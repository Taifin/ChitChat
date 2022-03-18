#ifndef CLIENT_USER_H
#define CLIENT_USER_H

#include "sprite.h"
#include "user.h"

class client_user : public user
{

public:
    client_user(std::string uname, std::string upwd);
    sprite *user_sprite = new sprite;
    ~client_user();
private:

};

#endif // CLIENT_USER_H
