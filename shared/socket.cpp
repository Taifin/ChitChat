#include "socket.h"
#include <QTcpServer>
#include "iostream"

namespace network {

void query_processor::prepare_query(const std::string &q, QTcpSocket *cli) {
    keeper->prepared_queries.push({q.c_str(), cli});
    emit prepared();
}

void query_processor::wait_next_query() {
    std::unique_lock lock(keeper->queries_mutex);
    keeper->query_available.wait(
        lock, [&]() { return !keeper->parsed_queries.empty(); });
    process();
}

tcp_socket::tcp_socket(const QHostAddress &host,
                       quint16 port,
                       queries_keeper *keeper1,
                       QObject *parent) {
    server = new QTcpServer(this);
    server->listen(host, port);
    qDebug() << "Started listening at:" << server->serverPort();
    keeper = keeper1;
    connect(server, SIGNAL(newConnection()), this, SLOT(connect_one()));
}

std::vector<std::string> query_processor::parse(const std::string &raw_data) {
    std::vector<std::string> parsed;
    std::istringstream raw_query(raw_data);
    std::string token;
    while (std::getline(raw_query, token, ',')) {
        parsed.push_back(token);
    }
    if (parsed.back().back() == '\n') {
        parsed.back().pop_back();
    }
    qDebug() << "Parsed:" << parsed[0].c_str();
    return parsed;
}

void tcp_socket::send() {
    auto q = keeper->prepared_queries.front();
    keeper->prepared_queries.pop();
    qDebug() << "Sending...";
    q.second->write(q.first);
    q.second->waitForReadyRead(25);
}

void tcp_socket::read() {
    auto *sender = dynamic_cast<QTcpSocket *>(QObject::sender());
    QByteArray data = sender->readAll();
    std::unique_lock lock(keeper->queries_mutex);
    keeper->parsed_queries.push({data, sender});
    keeper->query_available.notify_one();
}

query_processor::query_processor(queries_keeper *keeper, tcp_socket &socket)
    : keeper(keeper), socket(socket) {
    connect(this, SIGNAL(prepared()), &socket, SLOT(send()));
}

void tcp_socket::connect_one() {
    QTcpSocket *new_socket = server->nextPendingConnection();
    connect(new_socket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(new_socket, SIGNAL(disconnected()), this, SLOT(disconnect_one()));
    sockets.push_back(new_socket);
}

void tcp_socket::disconnect_one() {
    auto *socket = dynamic_cast<QTcpSocket *>(QObject::sender());
    sockets.removeOne(socket);
}
QList<QTcpSocket *> tcp_socket::get_sockets() const {
    return sockets;
}
}  // namespace network