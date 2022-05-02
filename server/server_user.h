#ifndef CHITCHAT_SERVER_USER_H
#define CHITCHAT_SERVER_USER_H

#include <utility>

#include "socket.h"
#include "user.h"

class server_user : public user {
public:
    QTcpSocket *client;

    explicit server_user(std::string uname,
                         std::string upwd,
                         QTcpSocket *socket,  // NOLINT
                         int x = 0,
                         int y = 0)
        : user(std::move(uname), std::move(upwd), x, y), client(socket) {
    }


    bool operator==(const server_user &other) {
        return this->name() == other.name();
    }

    bool operator==(server_user &&other) {
        return this->name() == other.name();
    }

};

#endif  // CHITCHAT_SERVER_USER_H
