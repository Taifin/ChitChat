#ifndef CHITCHAT_VOICE_MANAGER_H
#define CHITCHAT_VOICE_MANAGER_H

#include "QAudioFormat"
#include "QAudioInput"
#include "QAudioOutput"
#include "QIODevice"
#include "QTimer"
#include "client_socket.h"
#include "socket.h"

namespace client {

class processor : public network::query_processor {
    Q_OBJECT
public:
    explicit processor(network::queries_keeper *keeper1,
                       network::tcp_socket &socket1,
                       QTcpSocket *tcpSocket);
    void process() override;

private:
    QAudioFormat format;
    QAudioInput *audioInput;
    QAudioOutput *audioOutput;
    QIODevice *outDevice;
    QIODevice *inDevice;
    QTcpSocket *audio_socket;
    QTimer *timer;
    bool muted;

public slots:
    void input_audio_on();

    void input_audio_off();

    void output_audio_on();

    void output_audio_off();

    void send();
};

}  // namespace client

#endif  // CHITCHAT_VOICE_MANAGER_H
