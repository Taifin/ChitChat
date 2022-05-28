#include "client_user.h"

client_user::client_user() : user("noname", "defaulpassword") {
}

client_user::client_user(std::string uname, std::string upwd)
    : user(uname, upwd) {
    // user_sprite->setRect(0, 0, 30, 30);
    // user_sprite->name_display->setPlainText((QString("uname")));
    // user_sprite->name_display->setPos(30, 30);
}

client_user::client_user(std::string uname, std::string upwd, int x, int y)
    : user(uname, upwd, x, y) {
    // user_sprite->setRect(0, 0, 30, 30);
    // user_sprite->setRect(0, 0, 30, 30);
}

void client_user::set_user_sprite() {
    this->user_sprite = new sprite(this->get_name(), this->skin);
}

client_user::~client_user() {
    // delete user_sprite;
}
