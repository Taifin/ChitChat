#ifndef CHITCHAT_VOICE_MANAGER_H
#define CHITCHAT_VOICE_MANAGER_H

#include "QAudioFormat"
#include "QAudioInput"
#include "QAudioOutput"
#include "QIODevice"
#include "socket.h"

// TODO: initialize voice module only after successful connection

namespace client {

class manager : public QObject {
    Q_OBJECT
private:
    network::queries_keeper *keeper;
    QTcpSocket *socket;
    QAudioFormat format;
public slots:
    void read();

public:
    explicit manager(const QHostAddress &host,
                     quint16 port,
                     network::queries_keeper *keeper,
                     QObject *parent = nullptr);

    QTcpSocket *get_socket();
};

class processor : public QObject {
    Q_OBJECT
public:
    explicit processor(client::manager &socket, network::queries_keeper *keeper);
    void wait_next_query();
    void process();
    void prepare_query(const QByteArray &q, QTcpSocket *cli);

private:
    network::queries_keeper* keeper;
    QAudioFormat format;
    QAudioInput *audioInput;
    manager &socket;
    QAudioOutput *audioOutput;
    QIODevice *device;

signals:
    void prepared();

};

}  // namespace client

#endif  // CHITCHAT_VOICE_MANAGER_H
