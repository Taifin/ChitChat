#ifndef CLIENT_USER_H
#define CLIENT_USER_H

#include "shared/user.h"
#include "sprite.h"

class client_user : public user {
    Q_OBJECT

public:
    client_user();
    client_user(const std::string &uname, const std::string &upwd);
    client_user(const std::string &uname,
                const std::string &upwd,
                const std::string &skin);
    client_user(const std::string &uname,
                const std::string &upwd,
                const std::string &skin,
                int x,
                int y);

    void set_user_sprite();
    sprite *user_sprite;

public slots:
    void change_skin(const std::string &skin);
};

#endif  // CLIENT_USER_H
