#ifndef CHITCHAT_USER_H
#define CHITCHAT_USER_H

#include <utility>
#include "QHostAddress"
#include "string"
#include "vector"

struct point {
    int x;
    int y;
};

class user {
    std::string username;
    std::string password;
    point coords;

public:
    explicit user(std::string uname, std::string upwd, int x = 0, int y = 0)
        : username(std::move(uname)),
          password(std::move(upwd)),
          coords({x, y}){};

    [[nodiscard]] const std::string &name() const {
        return username;
    }

    [[nodiscard]] const std::string &pwd() const {
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

    user &operator=(const user &other) {
        username = other.username;
        password = other.password;
        coords = other.coords;
        return *this;
    }

    void set_name(const std::string &name) {
        username = name;
    }
};

#endif  // CHITCHAT_USER_H
