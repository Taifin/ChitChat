#include "database.h"

namespace db {
// TODO: connection pool
// (there's no default connection pool functionality in libpqxx?)

void chitchat_database::local_connection(const std::string &dbname) {
    params = "dbname=" + dbname;
    users_connection = pqxx::connection(params);
}

void chitchat_database::connection(const std::string &dbname,
                                   const std::string &host,
                                   const std::string &port,
                                   const std::string &user) {
    params = "dbname=" + dbname + " host=" + host + " port=" + port +
             " user=" + user;
    users_connection = pqxx::connection(params);
}

void chitchat_database::debug_create_db() {
    pqxx::connection conn("dbname=postgres");
    pqxx::nontransaction creator(conn);
    creator.exec("CREATE DATABASE ChitChat");
    creator.commit();
}

void chitchat_database::debug_create_table() {
    pqxx::connection conn("dbname=chitchat");
    pqxx::work w(conn);
    w.exec(
        "CREATE TABLE IF NOT EXISTS users (uname VARCHAR(30), "
        "upassword VARCHAR(30));");  // TODO: avatar and visited rooms
    w.commit();
}
bool chitchat_database::create_user(User *new_user) {
    bool exists =
        execute_params("SELECT count(1) > 0 FROM users WHERE uname=$1;",
                       new_user->username)[0][0]
            .as<bool>();
    if (!exists) {
        execute_params("INSERT INTO users (uname, upassword) VALUES ($1, $2);",
                       new_user->username, new_user->password);
        return true;
    } else {
        return false;
    }
}

User chitchat_database::get_user_data(User *user) {
    auto raw_user_data =
        execute_params("SELECT 1 FROM users WHERE uname=$1;", user->username);
    if (raw_user_data.empty())
        throw no_user_found("No information returned");
    return User(raw_user_data[0]["uname"].as<std::string>(),
                raw_user_data[0]["upassword"].as<std::string>());
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
bool chitchat_database::authorize(const std::string &username,
                                  const std::string &given_password) {
    auto exists =
        execute_params("SELECT count(1) > 0 FROM users WHERE uname=$1;",
                       username)[0][0]
            .as<bool>();
    if (exists) {
        auto stored_password =
            execute_params("SELECT upassword FROM users WHERE uname=$1;",
                           username)[0][0]
                .as<std::string>();
        return given_password == stored_password;
    } else {
        throw no_user_found("Cannot find user to authorize.");
    }
}
}  // namespace db
