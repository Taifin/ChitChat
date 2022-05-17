#ifndef CHITCHAT_VOICE_MANAGER_H
#define CHITCHAT_VOICE_MANAGER_H

#include "QAudioFormat"
#include "QAudioInput"
#include "QAudioOutput"
#include "QIODevice"
#include "client_socket.h"
#include "socket.h"

// TODO: initialize voice module only after successful connection

namespace client {

class manager : public client_socket {
private:
    QTcpSocket *socket;
    QAudioFormat format;

public:
    explicit manager(const QHostAddress &host,
                     quint16 port,
                     QTcpSocket* ser,
                     network::queries_keeper *keeper,
                     QObject *parent);

    QTcpSocket *get_socket();
};

class processor : public network::query_processor {
    Q_OBJECT
public:
    explicit processor(network::queries_keeper *keeper1,
                       network::tcp_socket &socket1);
    void process() override;

private:
    QAudioFormat format;
    QAudioInput *audioInput;
    QAudioOutput *audioOutput;
    QIODevice *device;

};

}  // namespace client

#endif  // CHITCHAT_VOICE_MANAGER_H
