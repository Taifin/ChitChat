#ifndef CHITCHAT_SOCKET_H
#define CHITCHAT_SOCKET_H

#include <QCoreApplication>
#include <QNetworkDatagram>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
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
    std::queue<std::pair<std::string, QTcpSocket *>> parsed_queries;
    std::queue<std::pair<std::string, QTcpSocket *>> prepared_queries;
    std::condition_variable query_available;
    std::mutex queries_mutex;
};

class tcp_socket : public QObject {
    Q_OBJECT

protected:
    queries_keeper *keeper;
    QTcpServer *server;
    QList<QTcpSocket *> sockets;

public:
    explicit tcp_socket(const QHostAddress &host,
                        quint16 port,
                        queries_keeper *keeper1,
                        QObject *parent = nullptr);

    void wait_for_processed();
    /// Sends "msg" to client.

signals:

public slots:
    void read();
    /// While socket has pending datagrams, reads them into "queries", where
    /// they are stored as {data, from} pairs. The function is called
    /// automatically when readyRead() signal is emitted.

    void connect_one();

    void disconnect_one();

    void send();
};

class query_processor : public QObject {
    Q_OBJECT

protected:
    queries_keeper *keeper;
    tcp_socket &socket;
    std::vector<std::string> data;
    QTcpSocket *to;

public:
    explicit query_processor(queries_keeper *keeper, tcp_socket &socket);

    static std::vector<std::string> parse(const std::string &raw_data);

    void wait_next_query();

    virtual void process() = 0;

    void prepare_query(const std::string &q, QTcpSocket *cli);

signals:

    void prepared();
};
}  // namespace network

#endif  // CHITCHAT_SOCKET_H
