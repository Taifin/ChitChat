#include "model.h"

std::map<std::string, User> md::model::connected_users;

bool md::model::connect_user(const User& new_user) {
    if (connected_users.count(new_user.username) == false) {
        connected_users.emplace(new_user.username, new_user);
        return true;
    } else {
        return false;
    }
}
