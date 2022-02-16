#include "database.h"

namespace db {
// TODO: connection pool

chitchat_database::chitchat_database(const std::string &dbname) : name(dbname) {
    params = "dbname=" + dbname;
}

chitchat_database::chitchat_database(const std::string &dbname,
                                     const std::string &host,
                                     const std::string &port,
                                     const std::string &user) {
    params = "dbname=" + dbname + " host=" + host + " port=" + port +
             " user=" + user;
}

void chitchat_database::create_db() {
    pqxx::connection conn("dbname=postgres");
    pqxx::nontransaction creator(conn);
    creator.exec(
        R"(SELECT 'CREATE DATABASE " + name + "' WHERE NOT EXISTS (SELECT FROM pg_database WHERE datname='" + name + "');)");
    creator.commit();  // if throws, will throw into initialize_and_connect(),
                       // abort on destruction
}

void chitchat_database::create_table() {
    pqxx::connection conn("dbname= " + name);
    pqxx::work w(conn);
    w.exec(
        "CREATE TABLE IF NOT EXISTS users (Uname VARCHAR(30), "
        "Upassword VARCHAR(30));");  // TODO: avatar
    w.commit();  // if throws, will throw into initialize_and_connect(), abort
                 // on destruction
}

void chitchat_database::connect_and_prepare() {
    users_connection = pqxx::connection(params);
    users_connection.prepare("check_user",
                             "SELECT * FROM users WHERE 'Uname' = $1;");
    users_connection.prepare(
        "create_user", "INSERT INTO users (Uname, Upassword) VALUES ($1, $2);");
    users_connection.prepare("get_password",
                             "SELECT (Upassword) FROM users WHERE Uname=$1");
}

init_return_code chitchat_database::initialize_and_connect() noexcept {
    try {
        create_db();
        create_table();
        connect_and_prepare();
        return init_return_code::INIT_SUCCESS;
    } catch (pqxx::failure &error) {
        std::cerr << error.what() << std::endl;
        return init_return_code::INIT_FAILURE;
    }
}

user_return_code chitchat_database::create_user(const std::string &username,
                                                const std::string &password) {
    pqxx::work w(users_connection);
    bool exists;
    try {
        exists = w.exec("SELECT count(1) > 0 FROM users WHERE Uname='" +
                        username + "';")[0][0]
                     .as<bool>();
        w.commit();
    } catch (pqxx::failure &error) {
        w.abort();
        std::cerr << error.what() << std::endl;
        return user_return_code::USER_FAILURE;
    }
    pqxx::work w2(users_connection);  // w2 is used due to abortion in try-catch
                                      // block, otherwise abort of committed
                                      // transaction is called
    if (!exists) {
        try {
            w2.exec_prepared("create_user", username, password);
            w2.commit();
            return user_return_code::USER_SUCCESS;
        } catch (pqxx::failure &error) {
            w2.abort();
            std::cerr << error.what() << std::endl;
            return user_return_code::USER_FAILURE;
        }
    } else {
        return user_return_code::USER_DUPLICATE;
    }
}

auth_return_code chitchat_database::authenticate(
    const std::string &username,
    const std::string &provided_password) {
    pqxx::work w(users_connection);
    std::string password;
    try {
        password =
            w.exec_prepared("get_password", username)[0][0].as<std::string>();
        w.commit();
    } catch (pqxx::failure &error) {
        w.abort();
        std::cerr << error.what() << std::endl;
        return auth_return_code::AUTH_FAILURE;
    }
    return (password == provided_password ? auth_return_code::AUTH_SUCCESS
                                          : auth_return_code::AUTH_DENIED);
}

pqxx::result chitchat_database::execute_protected(
    const std::string &connection_params,
    const std::string &query) {
    pqxx::connection conn(connection_params);
    pqxx::work w(conn);
    try {
        pqxx::result res = w.exec(query);
        w.commit();
        return res;
    } catch (pqxx::failure &error) {
        w.abort();
        std::cerr << error.what() << std::endl;
    }
}

}  // namespace db
