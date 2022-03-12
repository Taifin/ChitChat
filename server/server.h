#ifndef CHITCHAT_SERVER_H
#define CHITCHAT_SERVER_H

#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include "database.h"
#include "socket.h"
#include "user.h"

/// +----------+----------------------------+------------------------------------------------------------------------------------------+
/// | command  |           format           |                                          return                                          |
/// +----------+----------------------------+------------------------------------------------------------------------------------------+
/// | login    | login,username,password    | ok: allowed,username; bad: denied,username; no_user_found: none,username; error: dberror |
/// | register | register,username,password | ok: created,username; duplicate: exists,username                                         |
/// | connect  | connect,username,password  | ok: connected,username; duplicate: exists,username                                       |
/// | greet    | hello,username             | Hello, username, I'm Server God!                                                         |
/// +----------+----------------------------+------------------------------------------------------------------------------------------+


namespace sv {
class controller : network::udp_socket {
    Q_OBJECT
private:
    enum class e_commands { LOGIN, REGISTER, CONNECT, GREET };
    std::map<std::string, e_commands> commands{
        {"login", e_commands::LOGIN},
        {"register", e_commands::REGISTER},
        {"connect", e_commands::CONNECT},
        {"hello", e_commands::GREET}};

public:
    explicit controller(const QHostAddress &host1,
                        quint16 port1,
                        const std::string &type1 = "server",
                        QObject *parent1 = nullptr);

    void process() override;

    void authorize_user(std::vector<std::string> &data,
                        const network::client &to);
    /// Calls to database's authorize(), exceptions are handled.
    /// Use it to authorize user on login screen.

    void register_user(std::vector<std::string> &data,
                       const network::client &to);
    /// Calls to database's create_user().
    /// Use it to make new user in database.

    void connect_user(std::vector<std::string> &data,
                      const network::client &to);
    /// Calls to model's connect_user().
    /// Use it to connect user to the room (in future).

    void greet(std::vector<std::string> &data, const network::client &to);
    /// Debugging: sends message in return.

    virtual ~controller(){};
};
}  // namespace sv
#endif