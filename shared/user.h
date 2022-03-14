#ifndef CHITCHAT_USER_H
#define CHITCHAT_USER_H

#include <utility>
#include "string"
#include "vector"
#include "QHostAddress"

struct point {
    int x;
    int y;
};

class user {
    const std::string username;
    const std::string password;
    point coords;

    // TODO: move to client?
    //    const std::string address;
    //    const int port;
    // TODO: list of visited rooms
    // TODO: avatar
public:
    explicit user(std::string uname, std::string upwd)
        : username(std::move(uname)),
          password(std::move(upwd)),
          coords({0, 0}){};

    [[nodiscard]] const std::string& name() const {
        return username;
    }

    [[nodiscard]] const std::string& pwd() const {
        return password;
    }

    point get_coords() {
        return coords;
    }

    void set_coords(int x, int y) {
        coords = {x, y};
    }
};

#endif  // CHITCHAT_USER_H
