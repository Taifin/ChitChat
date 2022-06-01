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
                int x,
                int y);

    void set_user_sprite();
    sprite *user_sprite;
    ~client_user() override;

public slots:
    void change_skin(const std::string &skin);
};

#endif  // CLIENT_USER_H
