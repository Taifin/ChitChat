#include "state.h"

namespace model {
std::map<std::string, server_user> state::connected_users;

bool state::connect_user(const server_user &new_user) {
    if (connected_users.count(new_user.get_name()) == false) {
        connected_users.emplace(new_user.get_name(), new_user);
        return true;
    } else {
        return false;
    }
}

void state::update_coords(const server_user &user_moved) {
    if (connected_users.count(user_moved.get_name()))
        connected_users.at(user_moved.get_name()).set_coords(user_moved.get_x(), user_moved.get_y());
    else
        qDebug() << "user" << user_moved.get_name().c_str() << "is not in the room";
}

std::vector<server_user> state::get_users() {
    std::vector<server_user> users;
    for (const auto &u : connected_users) {
        users.push_back(u.second);
    }
    return users;
}

void state::disconnect_user(const server_user &disc_user) {
    connected_users.erase(disc_user.get_name());
}

}  // namespace model