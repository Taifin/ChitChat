#ifndef CHITCHAT_DATABASE_H
#define CHITCHAT_DATABASE_H

#include <iostream>
#include <pqxx/pqxx>
#include <string>

namespace db {

enum class init_return_code { INIT_SUCCESS, INIT_FAILURE };
enum class user_return_code { USER_SUCCESS, USER_DUPLICATE, USER_FAILURE };
enum class auth_return_code { AUTH_SUCCESS, AUTH_DENIED, AUTH_FAILURE };

struct chitchat_database {
private:
    std::string name;
    std::string params;
    pqxx::connection users_connection;

    static void create_db();

    void create_table();

    void connect_and_prepare();

public:
    explicit chitchat_database(const std::string &dbname = "chitchat");
    /// Default c-tor, please call it while testing locally.

    explicit chitchat_database(const std::string &dbname,
                               const std::string &host,
                               const std::string &port,
                               const std::string &user);
    /// C-tor to create full connection string (for remote connections).

    init_return_code initialize_and_connect() noexcept;
    /// Call this method to initialize database, prepare connection and ensure
    /// all the databases/tables exists. All pqxx-exceptions are handled, their
    /// what() outputted into cerr.

    user_return_code create_user(const std::string &username,
                                 const std::string &password);
    /// USER_DUPLICATE is returned if user already exists, USER_SUCCESS if
    /// creation is successful, USER_FAILURE otherwise (or if some of the check
    /// throws).

    auth_return_code authenticate(const std::string &username,
                                  const std::string &provided_password);
    /// AUTH_SUCCESS returned if provided_password matches username's password
    /// in the database, AUTH_DENIED otherwise. If database exception is thrown,
    /// AUTH_FAILURE is returned.

    static pqxx::result execute_protected(const std::string &connection_params,
                                          const std::string &query);
    /// Executes custom sql-query and returns a result in pqxx-format.
    /// Connection params in postgresql format required (see
    /// https://www.postgresql.org/docs/10/libpq-connect.html#LIBPQ-CONNSTRING),
    /// exceptions are handled.
};
}  // namespace db

#endif  // CHITCHAT_DATABASE_H
