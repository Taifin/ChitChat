#include "socket.h"
#include "iostream"

namespace network {

void query_processor::prepare_query(const std::string &q,
                                    const network::client &cli) {
    keeper->prepared_queries.push({q, cli});
    emit prepared();
}

void query_processor::wait_next_query() {
    std::unique_lock lock(keeper->queries_mutex);
    keeper->query_available.wait(
        lock, [&]() { return !keeper->parsed_queries.empty(); });
    process();
}

udp_socket::udp_socket(const QHostAddress &host,
                       quint16 port,
                       queries_keeper *keeper1,
                       QObject *parent) {
    socket = new QUdpSocket(this);
    socket->bind(port);
    keeper = keeper1;
    qDebug() << "Server is running at:" << socket->localAddress().toString()
             << "and port is:" << socket->localPort();
    connect(socket, &QUdpSocket::readyRead, this,
            &udp_socket::readPendingDatagrams);
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

void udp_socket::send() {
    auto q = keeper->prepared_queries.front();
    keeper->prepared_queries.pop();
    qDebug() << "Sending";
    socket->writeDatagram(q.first.c_str(), q.second.address, q.second.port);
    socket->waitForReadyRead(25);
}

void udp_socket::readPendingDatagrams() {
    QNetworkDatagram datagram;
    while (socket->hasPendingDatagrams()) {
        datagram = socket->receiveDatagram();
        qDebug() << "Received new message from"
                 << datagram.senderAddress().toString() << "at"
                 << datagram.senderPort();
        std::unique_lock lock(keeper->queries_mutex);
        keeper->parsed_queries.push(
            {datagram.data().toStdString(),
             {datagram.senderAddress(), datagram.senderPort()}});
    }
    keeper->query_available.notify_one();
}

query_processor::query_processor(queries_keeper *keeper, udp_socket &socket)
    : keeper(keeper), socket(socket) {
    connect(this, SIGNAL(prepared()), &socket, SLOT(send()));
}
}  // namespace network
