#include "client_user.h"

client_user::client_user() : user("noname", "defaulpassword", "miku") {
}

client_user::client_user(const std::string &uname,
                         const std::string &upwd,
                         const std::string &skin)
    : user(uname, upwd, skin) {
    // user_sprite->name_display->setPlainText((QString("uname")));
    // user_sprite->name_display->setPos(30, 30);
}

client_user::client_user(const std::string &uname,
                         const std::string &upwd,
                         const std::string &skin,
                         int x,
                         int y)
    : user(uname, upwd, skin, x, y) {
    // user_sprite->setRect(0, 0, 30, 30);
    // user_sprite->setRect(0, 0, 30, 30);
}

void client_user::set_user_sprite() {
    this->user_sprite = new sprite(this->name(), this->skin);
}

void client_user::change_skin(const std::string &skin) {
    user_sprite->change_skin(skin);
}

client_user::~client_user() {
    // delete user_sprite;
}
