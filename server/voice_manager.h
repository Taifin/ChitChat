#ifndef CHITCHAT_VOICE_MANAGER_H
#define CHITCHAT_VOICE_MANAGER_H

#include "QAudioFormat"
#include "socket.h"

namespace server {

class manager : public QObject {
    Q_OBJECT
public:
//    network::queries_keeper<QByteArray> *keeper;
    QTcpServer *server;
    QList<QTcpSocket *> sockets;
    manager(const QHostAddress &address,
            quint16 i
//            network::queries_keeper<QByteArray> *pKeeper
            );
public slots:
    void read();
    void connect_one();

    void disconnect_one();

//    void send();
};

class processor : public QObject {
    Q_OBJECT
public:
    explicit processor(server::manager &socket,
                       network::queries_keeper<QByteArray> *keeper);
    void wait_next_query();
//    void process();
//    void prepare_query(const QByteArray &q, QTcpSocket *cli);

private:
    network::queries_keeper<QByteArray> *keeper;
    QAudioFormat format;
    manager &socket;

signals:

    void prepared();
};
}

#endif  // CHITCHAT_VOICE_MANAGER_H
