#ifndef CHITCHAT_MODEL_H
#define CHITCHAT_MODEL_H
#include "user.h"
#include "map"
#include "string"

namespace md {
class model {
private:
    static std::map<std::string, User> connected_users;

public:
    static bool connect_user(const User& new_user);
};
}

#endif  // CHITCHAT_MODEL_H
