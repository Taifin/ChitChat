#include "client_user.h"

client_user::client_user() : user("noname", "default", "skin") {
}

client_user::client_user(const std::string &uname, const std::string &upwd)
    : user(uname, upwd, "") {
}

client_user::client_user(const std::string &uname,
                         const std::string &upwd,
                         const std::string &skin,
                         int x,
                         int y)

    : user(uname, upwd, "", x, y) {
}

void client_user::set_user_sprite() {
    this->user_sprite = new sprite(this->get_name(), this->get_skin());
    user_sprite->change_skin(get_skin());
}

void client_user::change_skin(const std::string &new_skin) {
    qDebug() << new_skin.c_str();
    this->set_skin(new_skin);
}
