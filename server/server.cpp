#include "server.h"
#include "model.h"

namespace sv {

controller::controller(const QHostAddress &host1,
                       quint16 port1,
                       QObject *parent1)
    : udp_socket(host1, port1, parent1) {
}

void controller::process() {
    while (!queries.empty()) {
        auto query = queries.front();
        queries.pop();
        auto data = parse(query.first);
        try {
            switch (commands.at(data[0])) {
                case e_commands::LOGIN:
                    authorize_user(data, query.second);
                    break;
                case e_commands::REGISTER:
                    register_user(data, query.second);
                    break;
                case e_commands::CONNECT:
                    connect_user(data, query.second);
                    break;
                case e_commands::GREET:
                    greet(data, query.second);
                    break;
            }
        } catch (std::out_of_range &e) {
            std::string unknown_cmd("Unknown token " + data[0] + "\n");
            socket->writeDatagram(unknown_cmd.c_str(), query.second.address,
                                  query.second.port);
        }
    }
}

void controller::authorize_user(std::vector<std::string> &data,
                                const network::client &to) {
    assert(data.size() == 3);
    try {
        if (db::chitchat_database::authorize(data[1], data[2])) {
            send_datagram("allowed," + data[1] + "\n", to);
        } else {
            send_datagram("denied," + data[1] + "\n", to);
        }
    } catch (db::no_user_found &) {
        send_datagram("none," + data[1] + "\n", to);
    } catch (db::database_error &) {
        send_datagram("dberror\n", to);
    }
}

void controller::register_user(std::vector<std::string> &data,
                               const network::client &to) {
    // TODO: complete user class
    assert(data.size() == 3);
    User new_user(data[1], data[2]);
    if (db::chitchat_database::create_user(&new_user)) {
        send_datagram("created," + data[1] + "\n", to);
    } else {
        send_datagram("exists," + data[1] + "\n", to);
    }
}

void controller::connect_user(std::vector<std::string> &data,
                              const network::client &to) {
    assert(data.size() == 3);
    User new_user{data[1], data[2]};
    if (md::model::connect_user(new_user)) {
        send_datagram("connected," + data[1] + "\n", to);
    } else {
        send_datagram("exists," + data[1] + "\n", to);
    }
}

void controller::greet(std::vector<std::string> &data,
                       const network::client &to) {
    assert(data.size() == 2);
    send_datagram("Hello, " + data[1] + ", I'm Server God!\n", to);
}

}  // namespace sv