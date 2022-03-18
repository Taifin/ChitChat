#ifndef CHITCHAT_DATABASE_H
#define CHITCHAT_DATABASE_H

#include <iostream>
#include <string>
#include "pqxx/pqxx"
#include "user.h"

namespace model {

struct database_error : std::runtime_error {
    explicit database_error(const std::string &msg) : std::runtime_error(msg){};
};

struct no_user_found : database_error {
    explicit no_user_found(const std::string &msg) : database_error(msg){};
};

struct database {
private:
    inline static std::string params;
    inline static pqxx::connection users_connection;

public:
    static void local_connection(const std::string &dbname = "chitchat");
    /// Default connector.

    static void connection(const std::string &dbname,
                           const std::string &host,
                           const std::string &port,
                           const std::string &user);
    /// Connector to establish full remote connection.

    static void debug_create_db();
    /// Use this method if you need to create database "ChitChat" locally (and
    /// ensure that your default postgres user in $PGUSER has all rights).

    static void debug_create_table();
    /// Use this method if you need to create table "users" in "ChitChat"
    /// database locally (and ensure that your default postgres user in $PGUSER
    /// has all rights).

    static bool create_user(user *new_user);
    /// true if user is created, false if duplicate

    template <typename... Args>
    static pqxx::result execute_params(const std::string &params_query,
                                       Args... args) {
        pqxx::work work(users_connection);
        auto result = work.exec_params(params_query, args...);
        work.commit();
        return result;
    };
    /// Accepts parametrized query and variadic number of argument to pass them
    /// to query.

    static bool authorize(const std::string &username,
                          const std::string &given_password);
    /// Checks if user's password stored in database matches given_password. If
    /// no such user found, no_user_found is thrown.

    static user get_user_data(user *user_);
    /// Returns object of User class with fields initialized with data from
    /// user's filed from database. If no user in records, no_user_found is
    /// thrown.

    static pqxx::result execute_protected(const std::string &connection_params,
                                          const std::string &query);
    /// Executes custom sql-query and returns a result in pqxx-format.
    /// Connection params in postgresql format required (see
    /// https://www.postgresql.org/docs/10/libpq-connect.html#LIBPQ-CONNSTRING),
    /// exceptions are handled.
};
}  // namespace model
#endif  // CHITCHAT_DATABASE_H
