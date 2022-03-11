#ifndef CHITCHAT_USER_H
#define CHITCHAT_USER_H

#include <utility>
#include "string"
#include "vector"

struct User {
    const std::string username;
    // TODO: separate username and login
    const std::string password;

    // TODO: move to client?
//    const std::string address;
//    const int port;
    // TODO: list of visited rooms
    // TODO: avatar

    explicit User(std::string uname,
                  std::string upwd)
        : username(std::move(uname)),
          password(std::move(upwd)) {};
};

#endif  // CHITCHAT_USER_H
