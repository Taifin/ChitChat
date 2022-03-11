#include "server.h"
#include "model.h"

namespace sv {

controller::controller(const QHostAddress &host, qint16 port, QObject *parent)
    : QObject(parent) {
    server_socket = new QUdpSocket(this);
    server_socket->bind(host, port);
    qDebug() << "Server running at:" << host.toString()
             << "and port is:" << port;
    readPendingDatagrams();
    connect(server_socket, &QUdpSocket::readyRead, this,
            &controller::readPendingDatagrams);
}

void controller::readPendingDatagrams() {
    QNetworkDatagram datagram;
    while (server_socket->hasPendingDatagrams()) {
        qDebug() << "Reading...";
        datagram = server_socket->receiveDatagram();
        qDebug() << "Received new message from"
                 << datagram.senderAddress().toString() << "at"
                 << datagram.senderPort();
        queries.push({datagram.data().toStdString(),
                      {datagram.senderAddress(), datagram.senderPort()}});
    }
    process();  // TODO
}

std::vector<std::string> controller::parse(const std::string &data) {
    std::vector<std::string> parsed;
    std::istringstream raw_query(data);
    std::string token;
    while (std::getline(raw_query, token, ',')) {
        parsed.push_back(token);
    }
    parsed.back().pop_back(); // removing leading '\n'
    return parsed;
}

void controller::greet(std::vector<std::string> &data, const sv::sender &to) {
    assert(data.size() == 2);
    send_datagram("Hello, " + data[1] + ", I'm Server God!\n", to);
}

void controller::process() {
    while (!queries.empty()) {
        auto query = queries.front();
        queries.pop();
        auto data = parse(query.first);
        try {
            switch (commands.at(data[0])) {
                case e_commands::LOGIN:
                    login_placeholder();
                    break;
                case e_commands::REGISTER:
                    register_placeholder();
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
            server_socket->writeDatagram(
                unknown_cmd.c_str(), query.second.address, query.second.port);
        }
    }
}
void controller::connect_user(std::vector<std::string> &data, const sv::sender &to) {
    assert(data.size() == 3);
    User new_user{data[1], data[2]};
    if (md::model::connect_user(new_user)) {
        send_datagram("connected," + data[1] + "\n", to);
    } else {
        send_datagram("exists," + data[1] + "\n", to);
    }
}
void controller::send_datagram(const std::string &msg, const sv::sender &to) {
    QByteArray data(msg.c_str());
    server_socket->writeDatagram(data, to.address, to.port);
}
}  // namespace sv