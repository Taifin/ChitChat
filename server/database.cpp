#include "database.h"

namespace model {

void database::local_connection(const std::string &dbname) {
    params = "dbname=" + dbname;
    users_connection = pqxx::connection(params);
}

void database::connection(const std::string &dbname,
                          const std::string &host,
                          const std::string &port,
                          const std::string &user) {
    params = "dbname=" + dbname + " host=" + host + " port=" + port +
             " user=" + user;
    users_connection = pqxx::connection(params);
}

bool database::create_user(const user &new_user) {
    bool exists =
        execute_params("SELECT count(1) > 0 FROM users WHERE uname=$1;",
                       new_user.get_name())[0][0]
            .as<bool>();
    if (!exists) {
        execute_params(
            "INSERT INTO users (uname, upassword, skin) VALUES ($1, $2, $3);",
            new_user.get_name(), new_user.get_password(), new_user.get_skin());
        return true;
    } else {
        return false;
    }
}

void database::change_values(const std::string &username,
                             const std::string &column_name,
                             const std::string &new_value) {
    // TODO: map on column name, because exec_params do not support variable
    // column name
    if (column_name == "arkanoid_score") {
        auto r = execute_params(
            "UPDATE users SET arkanoid_score = $1 WHERE uname = $2;",
            std::stoi(new_value), username);
    } else if (column_name == "hangman_score") {
        execute_params("UPDATE users SET hangman_score = $1 WHERE uname = $2;",
                       std::stoi(new_value), username);
    } else if (column_name == "skin") {
        execute_params("UPDATE users SET skin = $1 WHERE uname = $2;",
                       new_value, username);
    }
}

user database::get_user_data(const std::string &username) {
    auto raw_user_data =
        execute_params("SELECT * FROM users WHERE uname=$1;", username);
    if (raw_user_data.empty())
        throw no_user_found("No information returned");
    return user(raw_user_data[0]["uname"].as<std::string>(),
                raw_user_data[0]["upassword"].as<std::string>(),
                raw_user_data[0]["skin"].as<std::string>());
}

int database::get_user_score(const std::string& username, const std::string& gamename) {
    auto raw_user_data = execute_params("SELECT * FROM users WHERE uname=$1;", username);
    if (raw_user_data.empty())
        throw no_user_found("No information returned");
    return raw_user_data[0][gamename].as<int>();
}

pqxx::result database::execute_protected(const std::string &connection_params,
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

bool database::authorize(const std::string &username,
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
}  // namespace model