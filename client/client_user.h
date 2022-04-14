#ifndef CLIENT_USER_H
#define CLIENT_USER_H

#include "sprite.h"
#include "user.h"

class client_user : public user
{

public:
    client_user();
    client_user(std::string uname, std::string upwd);
    client_user(std::string uname, std::string upwd, int x, int y);
    sprite *user_sprite = new sprite(this->name());
    ~client_user();
private:

};

#endif // CLIENT_USER_H