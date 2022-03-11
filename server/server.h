#ifndef CHITCHAT_SERVER_H
#define CHITCHAT_SERVER_H

#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include "database.h"
#include "socket.h"
#include "user.h"

namespace sv {
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
                        QObject *parent1 = nullptr);

    static std::vector<std::string> parse(const std::string &data);

    void process() override;

    void authorize_user(std::vector<std::string> &data,
                        const network::client &to);

    void register_user(std::vector<std::string> &data,
                       const network::client &to);

    void connect_user(std::vector<std::string> &data,
                      const network::client &to);

    void greet(std::vector<std::string> &data, const network::client &to);

    virtual ~controller(){};
};
}  // namespace sv
#endif