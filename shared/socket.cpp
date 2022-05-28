#include "socket.h"
#include <QTcpServer>
#include "iostream"
#include "message.pb.h"

namespace network {

void queries_keeper::push_parsed(const QByteArray& data, QTcpSocket *sender) {
    std::unique_lock lock(queries_mutex);
    parsed_queries.push({data, sender});
    query_available.notify_one();
}

void queries_keeper::push_prepared(const QByteArray &q, QTcpSocket *cli) {
    std::unique_lock lock(queries_mutex);
    prepared_queries.push({q, cli});
}

std::pair<QByteArray, QTcpSocket *> queries_keeper::front_parsed() {
    return parsed_queries.front();
}

std::pair<QByteArray, QTcpSocket *> queries_keeper::pop_parsed() {
    std::unique_lock lock(queries_mutex);
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
    keeper->push_prepared(q, cli);
    emit prepared();
}

void query_processor::prepare_query(const ChitChatMessage::Query &q,
                                    QTcpSocket *cli) {
    QByteArray array;
    q.SerializeToArray(array.data(), sizeof(ChitChatMessage::Query));
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
    auto q = keeper->pop_prepared();
    qDebug() << "Sending...";
    q.second->write(q.first);
    q.second->waitForReadyRead(25);
}

void tcp_socket::read() {
    qDebug() << "New msg";
    auto *sender = dynamic_cast<QTcpSocket *>(QObject::sender());
    QByteArray data = sender->read(sizeof(ChitChatMessage::Query)); // TODO: sizeof??
    keeper->push_parsed(data, sender);
}

query_processor::query_processor(queries_keeper *keeper, tcp_socket &socket)
    : keeper(keeper), socket(socket) {
    connect(this, SIGNAL(prepared()), &socket, SLOT(send()));
}

}  // namespace network