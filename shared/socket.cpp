#include "socket.h"
#include <google/protobuf/descriptor.h>
#include <QTcpServer>
#include "istream"
#include "message.pb.h"

namespace network {

void queries_keeper::push_parsed(const QByteArray &data, QTcpSocket *sender) {
    std::unique_lock lock(queries_mutex);
    parsed_queries.push({data, sender});
    query_available.notify_one();
}

void queries_keeper::push_prepared(const QByteArray &q, QTcpSocket *cli) {
    prepared_queries.push({q, cli});
}

std::pair<QByteArray, QTcpSocket *> queries_keeper::front_parsed() {
    return parsed_queries.front();
}

std::pair<QByteArray, QTcpSocket *> queries_keeper::pop_parsed() {
    auto q = parsed_queries.front();
    parsed_queries.pop();
    return q;
}

std::pair<QByteArray, QTcpSocket *> queries_keeper::pop_prepared() {
    auto q = prepared_queries.front();
    prepared_queries.pop();
    return q;
}

std::atomic_size_t queries_keeper::parsed_size() const {
    return parsed_queries.size();
}

void query_processor::prepare_query(const QByteArray &q, QTcpSocket *cli) {
    qDebug() << "Preparing audio query, sending to" << cli->peerPort();
    auto size = q.size();
    QByteArray array(reinterpret_cast<const char *>(&size), 4);
    array.append(q);
    keeper->push_prepared(array, cli);
    emit prepared();
}

void query_processor::prepare_query(const ChitChatMessage::Query &q,
                                    QTcpSocket *cli) {
    qDebug() << "Preparing query, msg is:" << q.DebugString().c_str();
    qDebug() << "Size is:" << q.ByteSizeLong();
    auto size = q.ByteSizeLong();
    QByteArray array(reinterpret_cast<const char *>(&size), 4);
    array.append(q.SerializeAsString().data(), size);  // NOLINT
    keeper->push_prepared(array, cli);
    emit prepared();
}

void query_processor::wait_next_query() {
    std::unique_lock lock(keeper->queries_mutex);
    keeper->query_available.wait(lock,
                                 [&]() { return keeper->parsed_size() > 0; });
    process();
}

tcp_socket::tcp_socket(const QHostAddress &host,
                       quint16 port,
                       queries_keeper *keeper1,
                       QObject *parent) {
    qDebug() << "Socket created!";
    keeper = keeper1;
}

void tcp_socket::send() {
    auto q = keeper->pop_prepared();
    qDebug() << "Sending msg of size:" << q.first.size();
    q.second->write(q.first);
}

void tcp_socket::read() {
    auto *sender = dynamic_cast<QTcpSocket *>(QObject::sender());
    qDebug() << sender->localPort() << "reading new message...";
    while (sender->bytesAvailable() < 4) {
        sender->waitForBytesWritten(30);
        qDebug() << "Waiting for size arrival";
    }
    auto msg_size = *reinterpret_cast<quint32 *>(sender->read(4).data());
    while (sender->bytesAvailable() < msg_size) {
        sender->waitForBytesWritten(30);
        qDebug() << "Waiting for message arrival";
    }
    auto msg = sender->read(msg_size);
    keeper->push_parsed(msg, sender);
}

query_processor::query_processor(queries_keeper *keeper, tcp_socket &socket)
    : keeper(keeper), socket(socket) {
    connect(this, SIGNAL(prepared()), &socket, SLOT(send()));
}

}  // namespace network