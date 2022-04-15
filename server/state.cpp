#include "state.h"

namespace model {
std::map<std::string, server_user> state::connected_users;

bool state::connect_user(const server_user &new_user) {
  if (connected_users.count(new_user.name()) == false) {
    connected_users.emplace(new_user.name(), new_user);
    return true;
  } else {
    return false;
  }
}

void state::update_coords(const std::string &username, int x, int y) {
  connected_users.at(username).set_coords(x, y);
}
std::vector<server_user> state::get_users() {
  std::vector<server_user> users;
  for (const auto &u : connected_users) {
    users.push_back(u.second);
  }
  return users;
}

void state::disconnect_user(const server_user &disc_user) {
  connected_users.erase(disc_user.name());
}
}