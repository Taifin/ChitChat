#include "socket.h"
#include <QTcpServer>
#include "istream"
#include "message.pb.h"
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

namespace network {

void queries_keeper::push_parsed(const QByteArray& data, QTcpSocket *sender) {
    std::unique_lock lock(queries_mutex);
    parsed_queries.push({data, sender});
    query_available.notify_one();
}

void queries_keeper::push_prepared(const QByteArray &q, QTcpSocket *cli) {
//    std::unique_lock lock(queries_mutex);
    prepared_queries.push({q, cli});
}

std::pair<QByteArray, QTcpSocket *> queries_keeper::front_parsed() {
    return parsed_queries.front();
}

std::pair<QByteArray, QTcpSocket *> queries_keeper::pop_parsed() {
//    std::unique_lock lock(queries_mutex);
    auto q = parsed_queries.front();
    parsed_queries.pop();
    return q;
}

std::pair<QByteArray, QTcpSocket *> queries_keeper::pop_prepared() {
    std::unique_lock lock(queries_mutex);
    auto q = prepared_queries.front();
    prepared_queries.pop();
    return q;
}

std::atomic_size_t queries_keeper::parsed_size() const {
    return parsed_queries.size();
}

void query_processor::prepare_query(const QByteArray &q, QTcpSocket *cli) {
    auto size = q.size();
    QByteArray array(reinterpret_cast<const char*>(&size), 4);
    array.append(q); // TODO: prepend??
    keeper->push_prepared(array, cli);
    emit prepared();
}

void query_processor::prepare_query(const ChitChatMessage::Query& q,
                                    QTcpSocket *cli) {
    qDebug() << "Preparing query, msg is:" << q.DebugString().c_str();
    qDebug() << "Size is:" << q.ByteSizeLong();
    auto size = q.ByteSizeLong();
    QByteArray array(reinterpret_cast<const char*>(&size), 4);
    array.append(q.SerializeAsString().data(), size);
    keeper->push_prepared(array, cli);
    emit prepared();
}

void query_processor::wait_next_query() {
    std::unique_lock lock(keeper->queries_mutex);
    keeper->query_available.wait(
        lock, [&]() { return keeper->parsed_size() > 0; });
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
    q.second->waitForBytesWritten(25);
}

void tcp_socket::read() {
    qDebug() << "Reading...";
    auto *sender = dynamic_cast<QTcpSocket *>(QObject::sender());
    while (sender->bytesAvailable() > 0) {
        auto msg_size = *reinterpret_cast<quint32*>(sender->read(4).data());
        qDebug() << "New message of size:" << msg_size;
        qDebug() << "Bytes available after reading size:" << sender->bytesAvailable();
        auto msg = sender->read(msg_size);
        ChitChatMessage::Query q;
        qDebug() << "Bytes available after reading whole msg:" << sender->bytesAvailable();
        keeper->push_parsed(msg, sender);
    }
}

query_processor::query_processor(queries_keeper *keeper, tcp_socket &socket)
    : keeper(keeper), socket(socket) {
    connect(this, SIGNAL(prepared()), &socket, SLOT(send()));
}

}  // namespace network