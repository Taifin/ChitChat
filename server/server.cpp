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
                case e_commands::MOVE:
                    update_layout(data, query.second);
                    break;
                case e_commands::GET:
                    translate_users_data(data, query.second);
                    break;
            }
        } catch (std::out_of_range &e) {
            send_datagram("Unknown command " + data[0] + "\n", query.second);
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
    user new_user(data[1], data[2]);
    if (db::chitchat_database::create_user(&new_user)) {
        send_datagram("created," + data[1] + "\n", to);
    } else {
        send_datagram("rexists," + data[1] + "\n", to);
    }
}

void controller::connect_user(std::vector<std::string> &data,
                              const network::client &to) {
    assert(data.size() == 3);
    server_user new_user{data[1], data[2], to};
    if (md::model::connect_user(new_user)) {
        send_datagram("connected," + data[1] + "\n", to);
    } else {
        send_datagram("cexists," + data[1] + "\n", to);
    }
}

void controller::greet(std::vector<std::string> &data,
                       const network::client &to) {
    assert(data.size() == 2);
    send_datagram("Hello, " + data[1] + ", I'm Server God!\n", to);
}

void controller::update_layout(std::vector<std::string> &data,
                               const network::client &to) {
    assert(data.size() == 4);
    md::model::update_coords(data[1], std::stoi(data[2]), std::stoi(data[3]));
    for (const auto& u : md::model::get_users()) {
        send_datagram(data[1] + "," + data[2] + "," + data[3] + "\n",
                      u.client);  // TODO: лажа
    }
}

void controller::translate_users_data(std::vector<std::string> &data,
                                      const network::client &to) {
    std::string all_users;
    for (auto u : md::model::get_users()) {
        all_users += u.name() + "," + std::to_string(u.get_coords().x) + "," + std::to_string(u.get_coords().y) + ",";
    }
    all_users.pop_back();
    all_users += "\n";
    send_datagram(all_users, to);
}

}  // namespace sv