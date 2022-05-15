#ifndef CHITCHAT_VOICE_MANAGER_H
#define CHITCHAT_VOICE_MANAGER_H

#include "QAudioFormat"
#include "QAudioInput"
#include "QAudioOutput"
#include "QIODevice"
#include "socket.h"

namespace client {

class manager : public QObject {
    Q_OBJECT
private:
    network::queries_keeper<QByteArray> *keeper;
    QTcpSocket *socket;
    QAudioFormat format;
    QAudioOutput *audioOutput;
    QIODevice *device;
public slots:
    void read();

public:
    explicit manager(const QHostAddress &host,
                     quint16 port,
//                     network::queries_keeper<QByteArray> *keeper,
                     QObject *parent = nullptr);

    QTcpSocket *get_socket();
};

class processor : public QObject {
    Q_OBJECT
public:
    explicit processor(client::manager &socket);
    void wait_next_query();
    void process();
    void prepare_query(const QByteArray &q, QTcpSocket *cli);

private:
    //    network::queries_keeper<QByteArray>* keeper;
    QAudioFormat format;
    QAudioInput *audioInput;
//    QAudioOutput *audioOutput;
//    QIODevice *device;
    manager &socket;

signals:
    void prepared();

public slots:
    void stopAudio();
};

}  // namespace client

#endif  // CHITCHAT_VOICE_MANAGER_H
