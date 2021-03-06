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
                         std::string skin,
                         QTcpSocket *socket,  // NOLINT
                         int x = 0,
                         int y = 0)
        : user(std::move(uname), std::move(upwd), std::move(skin), x, y),
          client(socket) {
    }

    server_user() = default;

    bool operator==(const server_user &other) const {
        return this->get_name() == other.get_name();
    }

    bool operator!=(const server_user &other) const {
        return !(*this == other);
    }
};

#endif  // CHITCHAT_SERVER_USER_H
