#include "server.h"

// Нажимаем Connect
// На сервер отправляется сигнал (?), что нужно законнектить пользователя
// Должно быть состояние: сколько пользователей уже есть и какие они (мапа?)
//

namespace sv {

std::pair<std::string, User> server::create_user(const std::string &user_data,
                                                 const QHostAddress &address,
                                                 int port) {
    std::istringstream raw_user(user_data);
    std::string fake;
    std::getline(raw_user, fake, ';');
    std::vector<std::string> real_user_data(2);
    for (int i = 0; i < 2; i++) {
        std::getline(raw_user, real_user_data[i], ';');
    }
    return {real_user_data[0],
            User(real_user_data[0], real_user_data[1],
                 address.toString().toStdString(), port)};
}

bool server::connect_user(const std::string &user_data,
                          const QHostAddress &address,
                          int port) {
    auto new_user = create_user(user_data, address, port);
    if (server_users.count(new_user.first)) {
        QByteArray data;
        data.append("User exists\n");
        server_socket->writeDatagram(data,
                                     QHostAddress(new_user.second.address.data()),
                                     new_user.second.port);
        // send signal that user exists
    } else {
        QByteArray data;
        data.append("User inserted successfully\n");
        server_socket->writeDatagram(data,
                                     QHostAddress(new_user.second.address.data()),
                                     new_user.second.port);
        server_users.insert(new_user);
        // send signal that user is connected and room's ui can be shown
    }
}

server::server(const QHostAddress &host, qint16 port, QObject *parent)
    : QObject(parent) {
    server_socket = new QUdpSocket(this);
    server_socket->bind(host, port);
    qDebug() << "Server running at: " << host << " and port is: " << port;
    readPendingDatagrams();
    connect(server_socket, &QUdpSocket::readyRead, this,
            &server::readPendingDatagrams);
}

void server::readPendingDatagrams() {
    std::vector<std::string> received;
    QNetworkDatagram datagram;
    while (server_socket->hasPendingDatagrams()) {
        qDebug() << "Reading...";
        datagram = server_socket->receiveDatagram();
        qDebug() << "Received new message from" << datagram.senderAddress()
                 << "at" << datagram.senderPort();
        received.push_back(datagram.data().toStdString());
    }
    if (!received.empty()) {
        std::cout << received[0] << std::endl;
        connect_user(received[0], datagram.senderAddress(),
                     datagram.senderPort());
    }
}
}  // namespace sv