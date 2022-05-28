#include "server.h"
#include <cassert>
#include "state.h"

namespace server {

void server_processor::process() {
    while (keeper->parsed_size() > 0) {
        auto query = keeper->pop_parsed();
        data = parse(query.first.toStdString());
        to = query.second;
        try {
            switch (commands.at(data[0])) {
                case e_commands::LOGIN:
                    authorize_user();
                    break;
                case e_commands::REGISTER:
                    register_user();
                    break;
                case e_commands::CONNECT:
                    connect_user();
                    break;
                case e_commands::GREET:
                    greet();
                    break;
                case e_commands::MOVE:
                    update_layout();
                    break;
                case e_commands::DISCONNECT:
                    disconnect();
                    break;
                case e_commands::SPRITE:
                    get_sprite();
                    break;
                case e_commands::CHANGE:
                    change_data();
                    break;
            }
        } catch (std::out_of_range &e) {
            prepare_query("Unknown command " + data[0] + "\n", query.second);
        }
    }
}

void server_processor::authorize_user() {
    assert(data.size() == 3);
    try {
        if (model::database::authorize(data[1], data[2])) {
            auto user = model::database::get_user_data(data[1]);
            prepare_query(
                "allowed," + user.name() + "," + user.get_skin() + "\n", to);
        } else {
            prepare_query("denied," + data[1] + "\n", to);
        }
    } catch (model::no_user_found &) {
        prepare_query("none," + data[1] + "\n", to);
    } catch (model::database_error &) {
        prepare_query("dberror\n", to);
    }
}

void server_processor::register_user() {
    //    assert(data.size() == 3);
    user new_user(data[1], data[2], data[3]);
    if (model::database::create_user(new_user)) {
        prepare_query("created," + data[1] + "\n", to);
    } else {
        prepare_query("rexists," + data[1] + "\n", to);
    }
}

void server_processor::connect_user() {
    //    assert(data.size() == 3);
    server_user new_user{data[1], data[2], "kermit", to};
    if (model::state::connect_user(new_user)) {
        translate_users_data();
        new_user_connected();
    } else {
        prepare_query("cexists," + data[1] + "\n", to);
    }
}

void server_processor::greet() {
    assert(data.size() == 2);
    prepare_query("Hello, " + data[1] + ", I'm Server God!\n", to);
}

void server_processor::update_layout() {
    // assert(data.size() == 4);
    // many move requests can glue together and only first of them will be
    // processed
    model::state::update_coords(data[1], std::stoi(data[2]),
                                std::stoi(data[3]));
    for (const auto &u : model::state::get_users()) {
        if (u.client != to) {
            prepare_query(
                "move," + data[1] + "," + data[2] + "," + data[3] + "\n",
                u.client);
        }
    }
}

void server_processor::translate_users_data() {
    std::string all_users = "connected,";
    // TODO
    for (const auto &u : model::state::get_users()) {
        all_users += u.name() + "," + std::to_string(u.get_coords().x) + "," +
                     std::to_string(u.get_coords().y) + "," + u.get_skin() +
                     ",";
    }
    if (all_users.back() == ',')
        all_users.pop_back();
    if (!all_users.empty())
        all_users += "\n";
    prepare_query(all_users, to);
}

void server_processor::disconnect() {
    //    assert(data.size() == 5);
    model::state::disconnect_user(server_user(data[1], data[2], "kermit", to,
                                              std::stoi(data[3]),
                                              std::stoi(data[4])));
    for (const auto &u : model::state::get_users()) {
        prepare_query("disconnected," + data[1] + "\n", u.client);
    }
}
server_processor::server_processor(network::queries_keeper *pKeeper,
                                   network::tcp_socket &socket)
    : query_processor(pKeeper, socket) {
}

void server_processor::new_user_connected() {
    for (const auto &u : model::state::get_users()) {
        if (u.name() != data[1]) {
            prepare_query("new," + data[1] + "\n", u.client);
        }
    }
}

server::audio_processor::audio_processor(network::queries_keeper *keeper,
                                         network::tcp_socket &socket)
    : network::query_processor(keeper, socket) {
}

void server::server_socket::connect_one() {
    qDebug() << "New connection";
    QTcpSocket *new_socket = tcp_server->nextPendingConnection();
    connect(new_socket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(new_socket, SIGNAL(disconnected()), this, SLOT(disconnect_one()));
    sockets.push_back(new_socket);
}

void server::server_socket::disconnect_one() {
    auto *socket = dynamic_cast<QTcpSocket *>(QObject::sender());
    sockets.removeOne(socket);
}

QList<QTcpSocket *> server::server_socket::get_connected_sockets() const {
    return sockets;
}

server_socket::server_socket(const QHostAddress &host,
                             quint16 port,
                             network::queries_keeper *keeper1,
                             QObject *parent)
    : tcp_socket(host, port, keeper1, parent) {
    tcp_server = new QTcpServer();
    tcp_server->listen(host, port);
    qDebug() << tcp_server->serverAddress() << tcp_server->serverPort();
    qDebug() << "Server listening on" << host << port;
    connect(tcp_server, SIGNAL(newConnection()), this, SLOT(connect_one()));
}

void server::audio_processor::process() {
    while (keeper->parsed_size() > 0) {
        for (auto &sock :
             dynamic_cast<server_socket &>(socket).get_connected_sockets()) {
            auto query = keeper->front_parsed();
            if (sock != query.second) {
                prepare_query(query.first.toStdString(), sock);
            }
        }
        keeper->pop_parsed();
    }
}

void server_processor::get_sprite() {
    auto user = model::database::get_user_data(data[1]);
    prepare_query("sprite," + data[1] + " " + user.get_skin() + "\n", to);
}

void server_processor::change_data() {
    model::database::change_values(data[2], data[1], data[3]);
    prepare_query("changed," + data[1] + "," + data[2] + "," + data[3] + "\n",
                  to);
}

}  // namespace server