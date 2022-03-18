#include "client_user.h"

client_user::client_user(std::string uname, std::string upwd) : user(uname, upwd)
{
    //user_sprite = new sprite();
    user_sprite->setRect(0, 0, 30, 30);
    //user_sprite->name_display->setPos(30, 30);
    //user_sprite.name_display.setText(QString("uname"));
}


client_user::~client_user()
{
    delete user_sprite;
}

