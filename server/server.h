#ifndef CHITCHAT_SERVER_H
#define CHITCHAT_SERVER_H

#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include "database.h"
//#include "server_query.pb.h"
#include "socket.h"
#include "user.h"

/// +------------+-----------------------------+------------------------------------------------------------------------------------------+
/// | command    |           format            |                                          return                                          |
/// +------------+-----------------------------+------------------------------------------------------------------------------------------+
/// | login      | login,username,password     | ok: allowed,username; bad: denied,username; no_user_found: none,username; error: dberror |
/// | register   | register,username,password  | ok: created,username; duplicate: rexists,username                                        |
/// | connect    | connect,username,password   | ok: connected,username; duplicate: cexists,username                                      |
/// | greet      | hello,username              | Hello, username, I'm Server God!                                                         |
/// | move       | move,username,x,y           | move,username,x,y                                                                        |
/// | disconnect | disconnect,username,pwd,x,y | disconnected                                                                             |
/// +------------+-----------------------------+------------------------------------------------------------------------------------------+

namespace sv {
class controller : network::udp_socket {
    Q_OBJECT
private:
    enum class e_commands { LOGIN, REGISTER, CONNECT, GREET, MOVE, GET, DISCONNECT };
    std::map<std::string, e_commands> commands{
        {"login", e_commands::LOGIN},     {"register", e_commands::REGISTER},
        {"connect", e_commands::CONNECT}, {"hello", e_commands::GREET},
        {"move", e_commands::MOVE},       {"get", e_commands::GET},
        {"disconnect", e_commands::DISCONNECT}};

public:
    explicit controller(const QHostAddress &host1,
                        quint16 port1,
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

    void translate_users_data(std::vector<std::string> &data,
                              const network::client &to);

    void update_layout(std::vector<std::string> &data,
                       const network::client &to);

    void disconnect(std::vector<std::string> &data,
                    const network::client &to);

    void greet(std::vector<std::string> &data, const network::client &to);
    /// Debugging: sends message in return.

    virtual ~controller(){};
};
}  // namespace sv
#endif