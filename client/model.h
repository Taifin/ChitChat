#ifndef MODEL_H
#define MODEL_H

#include <QApplication>
#include "client_socket.h"
#include "client_user.h"
#include "shared/socket.h"
#include "voice_manager.h"

static quint16 PORT = 1235;

class threads : public QThread {
    Q_OBJECT
public:
    threads(client_processor *processor) : processor(processor){};

protected:
    client_processor *processor;
    void run() {
        while (true) {
            processor->wait_next_query();
        }
    };
};

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
    threads thread;

    void set_curren_user(std::string name, std::string password);

    ~model();

private slots:
    void send_request(const std::string &message);
};

#endif  // MODEL_H
