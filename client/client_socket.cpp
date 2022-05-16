#include "client_socket.h"
#include "login.h"

client_socket::client_socket(const QHostAddress &host,
                             quint16 port,
                             QTcpSocket *ser,
                             network::queries_keeper *keeper,
                             QObject *parent = nullptr)
    : tcp_socket(host, port, keeper, parent) {
    connect(ser, SIGNAL(readyRead()), this, SLOT(read()));
}

void client_processor::process() {
    std::vector<std::string> data = parse(keeper->parsed_queries.front().first.toStdString());
    std::string status = data[0];
    keeper->parsed_queries.pop();

    if (status == "allowed") {
        emit run_successful_login(data[1]);
    }
    if (status == "denied") {
        emit run_wrong_password();
    }
    if (status == "none") {
        emit run_no_user();
    }
    if (status == "dberror") {
        emit run_error();
    }
    if (status == "created") {
        emit run_successful_registration();
    }
    if (status == "rexists") {
        emit run_duplicate();
    }
    if (status == "connected") {
        emit run_connect_with_room(data);
    }
    if (status == "cexists") {
        emit run_already_connected();
    }
    if (status == "move") {
        emit run_change_position(data[1], stoi(data[2]), stoi(data[3]));
    }
    if (status == "disconnected") {
        emit run_disconnect_roommate(data[1]);
    }
    if (status == "new") {
        qDebug() << "New connection: " << data[1].c_str();
        emit run_connect_roommate(data[1]);
    }
}
