#ifndef CHITCHAT_SOCKET_H
#define CHITCHAT_SOCKET_H

#include <QCoreApplication>
#include <QNetworkDatagram>
#include <QObject>
#include <QUdpSocket>
#include <queue>

namespace network {
struct client {
    QHostAddress address;
    int port;
};

class udp_socket : public QObject {
    Q_OBJECT
private:
    QUdpSocket *socket;

protected:
    std::queue<std::pair<std::string, client>> queries;

public:
    explicit udp_socket(const QHostAddress &host,
                        quint16 port,
                        QObject *parent = nullptr);

    void send_datagram(const std::string &data, const client &to);
    /// Sends "msg" to client.

    virtual void process() = 0;
    /// process() is called every time when readPendingDatagrams finishes.
    /// Please, be sure to implement process(), as it is pure virtual.
signals:

public slots:
    void readPendingDatagrams();
    /// While socket has pending datagrams, reads them into "queries", where
    /// they are stored as {data, from} pairs. The function is called
    /// automatically when readyRead() signal is emitted.
};
}  // namespace network

#endif  // CHITCHAT_SOCKET_H
