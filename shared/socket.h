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
#include "message.pb.h"
#include "user.h"

namespace network {

class queries_keeper {
    std::queue<std::pair<QByteArray, QTcpSocket *>> parsed_queries;
    std::queue<std::pair<QByteArray, QTcpSocket *>> prepared_queries;

public:
    std::mutex queries_mutex;
    std::condition_variable query_available;

    void push_parsed(const QByteArray &data, QTcpSocket *sender);

    void push_prepared(const QByteArray &q, QTcpSocket *cli);

    std::pair<QByteArray, QTcpSocket *> front_parsed();

    std::pair<QByteArray, QTcpSocket *> pop_parsed();

    std::pair<QByteArray, QTcpSocket *> pop_prepared();

    [[nodiscard]] std::atomic_size_t parsed_size() const;
};

class tcp_socket : public QObject {
    // TODO: class only for methods read() and send()?
    Q_OBJECT

protected:
    queries_keeper *keeper;

private:
    uint32_t read_msg_size(char* buf);

public:
    explicit tcp_socket(const QHostAddress &host,
                        quint16 port,
                        queries_keeper *keeper1,
                        QObject *parent = nullptr);

    void wait_for_processed();
    /// Sends "msg" to client.

public slots:

    void read();
    /// While socket has pending datagrams, reads them into "queries", where
    /// they are stored as {data, from} pairs. The function is called
    /// automatically when readyRead() signal is emitted.

    void send();
};

class query_processor : public QObject {
    Q_OBJECT

protected:
    queries_keeper *keeper;
    tcp_socket &socket;
    ChitChatMessage::Query query;
    QTcpSocket *to;

public:
    explicit query_processor(queries_keeper *keeper, tcp_socket &socket);

    static void parse(const QByteArray &raw_data, ChitChatMessage::Query &q);

    void wait_next_query();

    virtual void process() = 0;

    void prepare_query(const QByteArray &q, QTcpSocket *cli);

    void prepare_query(const ChitChatMessage::Query& q,
                       QTcpSocket *cli);

signals:

    void prepared();
};
}  // namespace network

#endif  // CHITCHAT_SOCKET_H
