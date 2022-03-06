#ifndef CHITCHAT_USER_H
#define CHITCHAT_USER_H

#include <utility>
#include "string"
#include "vector"

struct User {
    const std::string username;
    const std::string password;
    const std::string address;
    const int port;
    // TODO: list of visited rooms
    // TODO: avatar

    explicit User(std::string uname,
                  std::string upwd,
                  std::string uip,
                  int uport)
        : username(std::move(uname)),
          password(std::move(upwd)),
          address(std::move(uip)),
          port(uport){};
};

#endif  // CHITCHAT_USER_H
