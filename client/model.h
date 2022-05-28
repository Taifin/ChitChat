#ifndef MODEL_H
#define MODEL_H

#include <QApplication>
#include "client_socket.h"
#include "client_user.h"
#include "shared/socket.h"
#include "voice_manager.h"
#include "message.pb.h"

static quint16 PORT = 1235;

class model : public QObject {
    Q_OBJECT

public:
    model();
    // TODO: aboba
    QTcpSocket *data_socket = new QTcpSocket(this);
    QTcpSocket *audio_socket = new QTcpSocket(this);
    network::queries_keeper *keeper = new network::queries_keeper;
    network::queries_keeper *audio_keeper = new network::queries_keeper;

    client_socket socket;
    client_processor processor;
    client::processor audio_processor;

    void set_curren_user(std::string name, std::string password);

    ~model();

private slots:
    void send_request(ChitChatMessage::Query message);
};

#endif  // MODEL_H
