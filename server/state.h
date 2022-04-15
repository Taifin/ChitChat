#ifndef CHITCHAT_STATE_H
#define CHITCHAT_STATE_H
#include "server_user.h"
#include "map"
#include "string"

namespace model {
class state {
private:
  static std::map<std::string, server_user> connected_users;

public:
  static bool connect_user(const server_user &new_user);

  static void disconnect_user(const server_user &disc_user);

  static void update_coords(const std::string &username, int x, int y);

  static std::vector<server_user> get_users();
};
}
#endif  // CHITCHAT_STATE_H
