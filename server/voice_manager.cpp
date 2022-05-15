#include "voice_manager.h"
void server::manager::read() {
    qDebug() << "New msg";
    auto *sender = dynamic_cast<QTcpSocket *>(QObject::sender());
    QByteArray data = sender->readAll();
    qDebug() << data.data();
    sockets.front()->write(data);
//    std::unique_lock lock(keeper->queries_mutex);
//    keeper->parsed_queries.push({data, sender});
//    keeper->query_available.notify_one();
}
server::manager::manager(const QHostAddress &address,
                         quint16 i
//                         network::queries_keeper<QByteArray> *pKeeper
                         ) {
    server = new QTcpServer(this);
    server->listen(address, i);
//    keeper = pKeeper;
    qDebug() << "Listening";
    connect(server, SIGNAL(newConnection()), this, SLOT(connect_one()));
}
//void server::processor::wait_next_query() {
//    std::unique_lock lock(keeper->queries_mutex);
//    keeper->query_available.wait(
//        lock, [&]() { return !keeper->parsed_queries.empty(); });
//    process();
//}
//server::processor::processor(server::manager &socket,
//                             network::queries_keeper<QByteArray> *keeper)
//    : socket(socket), keeper(keeper) {
//    connect(this, SIGNAL(prepared()), &socket, SLOT(send()));
//}
void server::manager::connect_one() {
    qDebug() << "New connection";
    QTcpSocket *new_socket = server->nextPendingConnection();
    connect(new_socket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(new_socket, SIGNAL(disconnected()), this, SLOT(disconnect_one()));
    sockets.push_back(new_socket);
}

void server::manager::disconnect_one() {
    auto *socket = dynamic_cast<QTcpSocket *>(QObject::sender());
    sockets.removeOne(socket);
}
//void server::manager::send() {
//    auto q = keeper->prepared_queries.front();
//    keeper->prepared_queries.pop();
//    qDebug() << "Sending...";
//    q.second->write(q.first);
//    q.second->waitForReadyRead(25);
//}

//void server::processor::process() {
//    while (!keeper->parsed_queries.empty()) {
//        for (auto &sock : socket.sockets) {
//            prepare_query(keeper->parsed_queries.front().first, sock);
//        }
//    }
//}
//
//void server::processor::prepare_query(const QByteArray &q, QTcpSocket *cli) {
//    keeper->prepared_queries.push({q, cli});
//    emit prepared();
//}
