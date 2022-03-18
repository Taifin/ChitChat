#ifndef CHITCHAT_USER_H
#define CHITCHAT_USER_H

#include <utility>
#include "string"
#include "vector"
#include "QHostAddress"

class user {

    std::string username;
    std::string password;

    int x;
    int y;

    // TODO: move to client?
    //    const std::string address;
    //    const int port;
    // TODO: list of visited rooms
    // TODO: avatar
public:
    explicit user(std::string uname, std::string upwd)
        : username(std::move(uname)),
          password(std::move(upwd)),
          x(0), y(0){};

    [[nodiscard]] const std::string& name() const {
        return username;
    }

    [[nodiscard]] const std::string& pwd() const {
        return password;
    }


    int get_x() {
        return x;
    }

    int get_y() {
        return y;
    }

    void set_x(int x_) {
        x = x_;
    }

    void set_y(int y_) {
        x = y_;
    }

    void set_coordanates(int x_, int y_) {
        x = x_;
        y = y_;
    }

    void set_name(std::string n) {
        username = n;
    }


    void set_pass(std::string p) {
        password = p;
    }

};

#endif  // CHITCHAT_USER_H
