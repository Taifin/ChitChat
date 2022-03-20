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

    // TODO: list of visited rooms
    // TODO: avatar
public:
    explicit user(std::string uname, std::string upwd, int x = 0, int y = 0)
        : username(std::move(uname)),
          password(std::move(upwd)),
          coords({x, y}){};

    [[nodiscard]] const std::string& name() const {
        return username;
    }

    [[nodiscard]] const std::string& pwd() const {
        return password;
    }

    [[nodiscard]] point get_coords() const {
        return coords;
    }

    [[nodiscard]] int get_x() const {
        return coords.x;
    }

    [[nodiscard]] int get_y() const {
        return coords.y;
    }

    void set_coords(int x, int y) {
        coords = {x, y};
    }
};

#endif  // CHITCHAT_USER_H
