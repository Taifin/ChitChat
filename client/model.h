#ifndef MODEL_H
#define MODEL_H

#include <QApplication>
#include "client_socket.h"
#include "client_user.h"
#include "message.pb.h"
#include "shared/socket.h"
#include "voice_manager.h"

static quint16 PORT = 1235;

class model : public QObject {
    Q_OBJECT

public:
    model();
    QTcpSocket *data_socket = new QTcpSocket(this);
    QTcpSocket *audio_socket = new QTcpSocket(this);
    network::queries_keeper *keeper = new network::queries_keeper;
    network::queries_keeper *audio_keeper = new network::queries_keeper;

    client_socket socket;
    client_socket a_socket;
    client_processor processor;
    client::processor audio_processor;

    ~model() override;

private slots:
    void send_request(const ChitChatMessage::Query &message);
};

#endif  // MODEL_H
