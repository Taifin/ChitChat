#ifndef CHITCHAT_STATE_H
#define CHITCHAT_STATE_H
#include "map"
#include "server_user.h"
#include "string"

namespace model {
class state {
private:
    static std::map<std::string, server_user> connected_users;

public:
    static bool connect_user(const server_user &new_user);

    static void disconnect_user(const server_user &disc_user);

    static void update_coords(const server_user &user_moved);

    static std::vector<server_user> get_users();
};
}  // namespace model
#endif  // CHITCHAT_STATE_H
