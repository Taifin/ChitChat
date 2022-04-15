#include "client_socket.h"
#include "login.h"

client_socket::client_socket(const QHostAddress &host,
                             quint16 port,
                             network::queries_keeper *keeper,
                             QObject *parent = nullptr)
    : udp_socket(host, port, keeper, parent) {
}

void client_processor::process() {
    std::vector<std::string> data = parse(keeper->parsed_queries.front().first);
    std::string status = data[0];
    network::client current_client = keeper->parsed_queries.front().second;
    keeper->parsed_queries.pop();
    for (const auto &d : data) {
        qDebug() << d.c_str();
    }

    // case for login
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
    // case for registration
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
        qDebug() << "im dead";
        emit run_change_position(data[1], stoi(data[2]), stoi(data[3]));
    }
}
