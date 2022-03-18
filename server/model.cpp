#include "model.h"

std::map<std::string, server_user> md::model::connected_users;

bool md::model::connect_user(const server_user & new_user) {
    if (connected_users.count(new_user.name()) == false) {
        connected_users.emplace(new_user.name(), new_user);
        return true;
    } else {
        return false;
    }
}

void md::model::update_coords(const std::string &username, int x, int y) {
    connected_users.at(username).set_coords(x, y);
}
std::vector<server_user> md::model::get_users() {
    std::vector<server_user> users;
    for (const auto& u : connected_users) {
        users.push_back(u.second);
    }
    return users;
}

void md::model::disconnect_user(const server_user &disc_user) {
    connected_users.erase(disc_user.name());
}
