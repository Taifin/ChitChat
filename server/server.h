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

/// +------------+-----------------------------+------------------------------------------------------------------------------------------+
/// | command    |           format            | return |
/// +------------+-----------------------------+------------------------------------------------------------------------------------------+
/// | login      | login,username,password     | ok: allowed,username; bad:
/// denied,username; no_user_found: none,username; error: dberror | | register
/// | register,username,password  | ok: created,username; duplicate:
/// rexists,username                                        | | connect    |
/// connect,username,password   | ok: connected,user1,x1,y1,user2,x2,y2...;
/// duplicate: cexists,username                    | | greet      |
/// hello,username              | Hello, username, I'm Server God! | | move |
/// move,username,x,y           | move,username,x,y | | disconnect |
/// disconnect,username,pwd,x,y | disconnected |
/// +------------+-----------------------------+------------------------------------------------------------------------------------------+

namespace sv {

class server_socket : public network::tcp_socket {
public:
    explicit server_socket(const QHostAddress &host,
                           quint16 port,
                           network::queries_keeper *keeper1,
                           QObject *parent = nullptr)
        : network::tcp_socket(host, port, keeper1) {
    }
};

class server_processor : public network::query_processor {
    Q_OBJECT;

private:
    enum class e_commands { LOGIN, REGISTER, CONNECT, GREET, MOVE, DISCONNECT };
    std::map<std::string, e_commands> commands{
        {"login", e_commands::LOGIN},
        {"register", e_commands::REGISTER},
        {"connect", e_commands::CONNECT},
        {"hello", e_commands::GREET},
        {"move", e_commands::MOVE},
        {"disconnect", e_commands::DISCONNECT}};

public:
    void process() override;

    void authorize_user();
    /// Calls to database's authorize(), exceptions are handled.
    /// Use it to authorize user on login screen.

    void register_user();
    /// Calls to database's create_user().
    /// Use it to make new user in database.

    void connect_user();
    /// Calls to model's connect_user().
    /// Use it to connect user to the room (in future).

    void translate_users_data();

    void new_user_connected();

    void update_layout();

    void disconnect();

    void greet();
    /// Debugging: sends message in return.

    server_processor(network::queries_keeper *pKeeper,
                     network::tcp_socket &socket);
};

}  // namespace sv
#endif