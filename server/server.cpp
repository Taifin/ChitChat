#include "server.h"
#include "state.h"

namespace server {

using namespace ChitChatMessage;

void server_processor::process() {
    while (keeper->parsed_size() > 0) {
        auto raw_query = keeper->pop_parsed();
        query.ParseFromString(raw_query.first.toStdString());
        user_in_process.parse_from(query);
        user_in_process.client = raw_query.second;
        to = raw_query.second;
        switch (query.rtype()) {
            case Query_RequestType_LOGIN:
                authorize_user();
                break;
            case Query_RequestType_REGISTER:
                register_user();
                break;
            case Query_RequestType_CONNECT:
                connect_user();
                break;
            case Query_RequestType_MOVE:
                update_layout();
                break;
            case Query_RequestType_DISCONNECT:
                disconnect();
                break;
            case Query_RequestType_GET_SKIN:
                get_sprite();
                break;
            case Query_RequestType_CHANGE_SKIN:
                change_skin();
                break;
            case Query_RequestType_CHANGE_SCORE:
                change_score();
                break;
        }
    }
}

void server_processor::authorize_user() {
    try {
        if (model::database::authorize(user_in_process.get_name(),
                                       user_in_process.get_password())) {
            user_in_process.set_skin(
                model::database::get_user_data(user_in_process.get_name())
                    .get_skin());
            prepare_query(
                user_in_process.serialize(Query_FeedbackType_LOGIN_ALLOWED),
                to);
        } else {
            prepare_query(
                user_in_process.serialize(Query_FeedbackType_LOGIN_DENIED), to);
        }
    } catch (model::no_user_found &) {
        prepare_query(
            user_in_process.serialize(Query_FeedbackType_NO_USER_FOUND), to);
    } catch (model::database_error &) {
        prepare_query(
            user_in_process.serialize(Query_FeedbackType_DATABASE_ERROR), to);
    }
}

void server_processor::register_user() {
    if (model::database::create_user(user_in_process)) {
        prepare_query(
            user_in_process.serialize(Query_FeedbackType_USER_CREATED), to);
    } else {
        prepare_query(
            user_in_process.serialize(Query_FeedbackType_USER_DUPLICATE), to);
    }
}

void server_processor::connect_user() {
    if (model::state::connect_user(user_in_process)) {
        translate_users_data();
        new_user_connected();
    } else {
        prepare_query(
            user_in_process.serialize(Query_FeedbackType_CONNECTION_EXISTS),
            to);
    }
}

void server_processor::update_layout() {
    model::state::update_coords(user_in_process);
    for (const auto &u : model::state::get_users()) {
        if (u != user_in_process) {
            prepare_query(user_in_process.serialize(Query_FeedbackType_MOVED),
                          u.client);
        }
    }
}

void server_processor::translate_users_data() {
    Query all_users_query;
    all_users_query.set_ftype(
        ChitChatMessage::Query_FeedbackType_CONNECTION_SUCCESS);
    for (const auto &u : model::state::get_users()) {
        auto us = all_users_query.add_users();
        us->set_name(u.get_name());
        us->set_password(u.get_password());
        us->set_skin(u.get_skin());
        us->set_x_coord(u.get_x());
        us->set_y_coord(u.get_y());
    }
    prepare_query(all_users_query, to);
}

void server_processor::disconnect() {
    model::state::disconnect_user(user_in_process);
    for (const auto &u : model::state::get_users()) {
        prepare_query(
            user_in_process.serialize(Query_FeedbackType_DISCONNECTED),
            u.client);
    }
}
server_processor::server_processor(network::queries_keeper *pKeeper,
                                   network::tcp_socket &socket)
    : query_processor(pKeeper, socket) {
}

void server_processor::new_user_connected() {
    for (const auto &u : model::state::get_users()) {
        if (u != user_in_process) {
            prepare_query(user_in_process.serialize(
                              Query_FeedbackType_NEW_USER_CONNECTED),
                          u.client);
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
    qDebug() << "Server listening on" << tcp_server->serverAddress()
             << tcp_server->serverPort();
    connect(tcp_server, SIGNAL(newConnection()), this, SLOT(connect_one()));
}

void server::audio_processor::process() {
    while (keeper->parsed_size() > 0) {
        for (auto &sock :
             dynamic_cast<server_socket &>(socket).get_connected_sockets()) {
            auto query = keeper->front_parsed();
            if (sock != query.second) {
                prepare_query(query.first, sock);
            }
        }
        keeper->pop_parsed();
    }
}

void server_processor::get_sprite() {
    user_in_process.set_skin(
        model::database::get_user_data(user_in_process.get_name()).get_skin());
    prepare_query(user_in_process.serialize(Query_FeedbackType_SKIN), to);
}

void server_processor::change_skin() {
    qDebug() << "Changing skin...";
    model::database::change_values(user_in_process.get_name(), "skin",
                                   user_in_process.get_skin());
    prepare_query(user_in_process.serialize(Query_FeedbackType_SKIN_CHANGED),
                  to);
}
void server_processor::change_score() {
    qDebug() << "Changing score, game name is" << (query.game_name() + "_score").c_str();
    model::database::change_values(user_in_process.get_name(),
                                   query.game_name() + "_score",
                                   std::to_string(query.score()));
    prepare_query(user_in_process.serialize(Query_FeedbackType_SCORE_CHANGED),
                  to);
}

}  // namespace server