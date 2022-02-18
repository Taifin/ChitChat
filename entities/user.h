#ifndef CHITCHAT_USER_H
#define CHITCHAT_USER_H

#include <utility>

#include "string"
#include "vector"

struct User {
    const std::string username;
    const std::string password;
    // TODO: list of visited rooms
    // TODO: avatar

    explicit User(std::string  uname, std::string  upwd) : username(std::move(uname)), password(std::move(upwd)) {};
};

#endif  // CHITCHAT_USER_H
