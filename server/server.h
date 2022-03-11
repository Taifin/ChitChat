#ifndef CHITCHAT_SERVER_H
#define CHITCHAT_SERVER_H

#include "socket.h"
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include "user.h"

namespace sv {
// TODO: client??
struct sender {
    QHostAddress address;
    int port;
};

class controller : network::udp_socket {
    Q_OBJECT
private:
    enum class e_commands { LOGIN, REGISTER, CONNECT, GREET };
    std::map<std::string, e_commands> commands{
        {"login", e_commands::LOGIN},
        {"register", e_commands::REGISTER},
        {"connect", e_commands::CONNECT},
        {"hello", e_commands::GREET}};

public:
    explicit controller(const QHostAddress &host1,
                        quint16 port1,
                        QObject *parent1);

    std::vector<std::string> parse(const std::string &data);

    void process() override;

    void login_placeholder(){};

    void register_placeholder(){};

    void connect_user(std::vector<std::string> &data, const network::client &to);

    void greet(std::vector<std::string> &data, const network::client &to);

    virtual ~controller(){};
};
}  // namespace sv
#endif