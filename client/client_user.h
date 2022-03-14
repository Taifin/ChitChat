#ifndef CLIENT_USER_H
#define CLIENT_USER_H

#include "sprite.h"
#include "user.h"

class client_user : public User
{
public:
    client_user();
private:
    sprite *user_sprite;
};

#endif // CLIENT_USER_H
