#ifndef MODEL_H
#define MODEL_H

#include <QApplication>
#include "client_socket.h"
#include "client_user.h"
#include "shared/socket.h"
#include "voice_manager.h"

static quint16 PORT = 60000;

class model : public QObject {
    Q_OBJECT

public:
    model();
    // TODO: aboba
    QTcpSocket *remote_server = new QTcpSocket();
    network::queries_keeper *keeper = new network::queries_keeper;

    client_socket socket;
    client_processor processor;
    client::processor audio_processor;

    void set_curren_user(std::string name, std::string password);

    ~model();

private slots:
    void send_request(const std::string &message);
};

#endif  // MODEL_H
