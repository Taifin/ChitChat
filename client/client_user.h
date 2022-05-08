#ifndef CLIENT_USER_H
#define CLIENT_USER_H

#include "sprite.h"
#include "shared/user.h"

class client_user : public user {
public:
    client_user();
    client_user(std::string uname, std::string upwd);
    client_user(std::string uname, std::string upwd, int x, int y);
    void set_user_sprite();
    sprite *user_sprite;
    std::string skin = "pikachu";
    ~client_user();

private:

};

#endif  // CLIENT_USER_H
