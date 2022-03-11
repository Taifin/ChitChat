#include "socket.h"

namespace network {
udp_socket::udp_socket(const QHostAddress &host,
                       quint16 port,
                       QObject *parent) {
    socket = new QUdpSocket(this);
    socket->bind(host, port);
    qDebug() << "Server is running at:" << host << "and port is:" << port;
    connect(socket, &QUdpSocket::readyRead, this,
            &udp_socket::readPendingDatagrams);
}

void udp_socket::send_datagram(const std::string &data, const client &to) {
    QByteArray datagram(data.c_str());
    socket->writeDatagram(datagram, to.address, to.port);
}

void udp_socket::readPendingDatagrams() {
    QNetworkDatagram datagram;
    while (socket->hasPendingDatagrams()) {
        datagram = socket->receiveDatagram();
        qDebug() << "Received new message from"
                 << datagram.senderAddress().toString() << "at"
                 << datagram.senderPort();
        queries.push({datagram.data().toStdString(),
                      {datagram.senderAddress(), datagram.senderPort()}});
    }
    process();
}
}  // namespace network