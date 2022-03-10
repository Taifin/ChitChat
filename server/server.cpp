#include "server.h"

// Нажимаем Connect
// На сервер отправляется сигнал (?), что нужно законнектить пользователя
// Должно быть состояние: сколько пользователей уже есть и какие они (мапа?)
//

namespace sv {

//std::pair<std::string, User> controller::create_user(const std::string &user_data,
//                                                 const QHostAddress &address,
//                                                 int port) {
//    std::istringstream raw_user(user_data);
//    std::string fake;
//    std::getline(raw_user, fake, ';');
//    std::vector<std::string> real_user_data(2);
//    for (int i = 0; i < 2; i++) {
//        std::getline(raw_user, real_user_data[i], ';');
//    }
//    return {real_user_data[0], User(real_user_data[0], real_user_data[1],
//                                    address.toString().toStdString(), port)};
//}

//bool controller::connect_user(const std::string &user_data,
//                          const QHostAddress &address,
//                          int port) {
//    auto new_user = create_user(user_data, address, port);
//    QByteArray data;
//    if (!server_users.insert(new_user).second) {
//        data.append("User exists\n");
//        server_socket->writeDatagram(
//            data, QHostAddress(new_user.second.address.data()),
//            new_user.second.port);
//        return false;
//    } else {
//        data.append("User inserted successfully\n");
//        server_socket->writeDatagram(
//            data, QHostAddress(new_user.second.address.data()),
//            new_user.second.port);
//        return true;
//    }
//}

// TODO: connect reading and processing
controller::controller(const QHostAddress &host, qint16 port, QObject *parent)
    : QObject(parent) {
    server_socket = new QUdpSocket(this);
    server_socket->bind(host, port);
    qDebug() << "Server running at: " << host << " and port is: " << port;
    readPendingDatagrams();
    connect(server_socket, &QUdpSocket::readyRead, this,
            &controller::readPendingDatagrams);
}

void controller::readPendingDatagrams() {
    QNetworkDatagram datagram;
    while (server_socket->hasPendingDatagrams()) {
        qDebug() << "Reading...";
        datagram = server_socket->receiveDatagram();
        qDebug() << "Received new message from" << datagram.senderAddress()
                 << "at" << datagram.senderPort();
        queries.push({datagram.data().toStdString(), {datagram.senderAddress(), datagram.senderPort()}});
    }
    process(); // TODO
}

std::vector<std::string> controller::parse(const std::string &data) {
    std::vector<std::string> parsed;
    std::istringstream raw_query(data);
    std::string token;
    while (std::getline(raw_query, token, ',')) {
        parsed.push_back(token);
    }
    return parsed;
}

void controller::greet(std::vector<std::string> &data, const sv::sender& to) {
    assert(data.size() == 2);
    QByteArray to_send;
    std::string msg = "Hello, " + data[1] + ", I'm Server God!";
    to_send.append(msg.c_str());
    server_socket->writeDatagram(to_send, to.address, to.port);
}

void controller::process() {
    while (!queries.empty()) {
        auto query = queries.front();
        queries.pop();
        auto data = parse(query.first);
        switch (commands.at(data[0])) { // TODO: catch out_of_range
            case e_commands::LOGIN:
                login_placeholder();
                break;
            case e_commands::REGISTER:
                register_placeholder();
                break;
            case e_commands::CONNECT:
                connect_placeholder();
                break;
            case e_commands::GREET:
                greet(data, query.second);
                break;
        }
    }
}
}  // namespace sv