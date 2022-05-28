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
#include "server_user.h"

// clang-format off
/// +--------------+---------------------------------------------+----------------------------------------------------------------------------------------------+
/// |   command    |                   format                    |                                            return                                            |
/// +--------------+---------------------------------------------+----------------------------------------------------------------------------------------------+
/// | login        | login,username,password                     | ok: allowed,username,skin; bad:denied,username; no_user_found: none,username; error: dberror |
/// | register     | register,username,password                  | ok: created,username; duplicate: rexists,username                                            |
/// | connect      | connect,username,password                   | ok: connected,user1,x1,y1,skin1,user2,x2,y2,skin2...; duplicate: cexists,username            |
/// | hello        | hello,username                              | Hello, username, I'm Server God!                                                             |
/// | move         | move,username,x,y                           | move,username,x,y                                                                            |
/// | disconnect   | disconnect,username,get_password,skin,x,y            | disconnected,username                                                                        |
/// | change skin  | change,skin,username,new_skin               | changed,skin,username                                                                        |
/// | change score | change,*game_name*_score,username,new_score | changed,score,username                                                                       |
/// | sprite       | sprite,username                             | sprite,username                                                                              |
/// +--------------+---------------------------------------------+----------------------------------------------------------------------------------------------+
// clang-format on

namespace server {

class server_socket : public network::tcp_socket {
    Q_OBJECT
    QTcpServer *tcp_server;
    QList<QTcpSocket *> sockets;

public:
    explicit server_socket(const QHostAddress &host,
                           quint16 port,
                           network::queries_keeper *keeper1,
                           QObject *parent = nullptr);

    [[nodiscard]] QList<QTcpSocket *> get_connected_sockets() const;

public slots:
    void connect_one();

    void disconnect_one();
};

class server_processor : public network::query_processor {
    Q_OBJECT

private:
    server_user user_in_process;

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

    void get_sprite();

    void change_skin();

    void change_score();

    server_processor(network::queries_keeper *pKeeper,
                     network::tcp_socket &socket);
};

class audio_processor : public network::query_processor {
public:
    explicit audio_processor(network::queries_keeper *keeper,
                             network::tcp_socket &socket);

    void process() override;
};

}  // namespace sv
#endif