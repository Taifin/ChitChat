#ifndef CHITCHAT_SOCKET_H
#define CHITCHAT_SOCKET_H

#include <QCoreApplication>
#include <QNetworkDatagram>
#include <QObject>
#include <QUdpSocket>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

namespace network {
struct client {
    QHostAddress address;
    int port;
};

struct queries_keeper {
    std::queue<std::pair<std::string, client>> queries;
    std::condition_variable query_available;
    std::mutex queries_mutex;
};

class udp_socket : public QObject {
    Q_OBJECT

protected:
    queries_keeper *keeper;
    QUdpSocket *socket;

public:
    explicit udp_socket(const QHostAddress &host,
                        quint16 port,
                        queries_keeper* keeper1,
                        QObject *parent = nullptr);

    void send_datagram(const std::string &data, const client &to);
    /// Sends "msg" to client.

    virtual client configure_address(const QHostAddress &address) = 0;

signals:

public slots:
    void readPendingDatagrams();
    /// While socket has pending datagrams, reads them into "queries", where
    /// they are stored as {data, from} pairs. The function is called
    /// automatically when readyRead() signal is emitted.
};

class query_processor {
protected:
    queries_keeper *keeper;
    udp_socket &socket;
    std::vector<std::string> data;
    client to;

public:
    explicit query_processor(queries_keeper *keeper, udp_socket &socket)
        : keeper(keeper), socket(socket) {
    }

    static std::vector<std::string> parse(const std::string &raw_data);

    void set_keeper(queries_keeper *keeper1);

    void wait_next_query();

    virtual void process() = 0;
};
}  // namespace network

#endif  // CHITCHAT_SOCKET_H
