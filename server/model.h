#ifndef CHITCHAT_MODEL_H
#define CHITCHAT_MODEL_H
#include "server_user.h"
#include "map"
#include "string"

namespace md {
class model {
private:
    static std::map<std::string, server_user> connected_users;

public:
    static bool connect_user(const server_user & new_user);

    static void disconnect_user(const server_user & disc_user);

    static void update_coords(const std::string &username, int x, int y);

    static std::vector<server_user> get_users();
};
}

#endif  // CHITCHAT_MODEL_H
