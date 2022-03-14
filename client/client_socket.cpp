#include "client_socket.h"
#include "login.h"

client_socket::client_socket(const QHostAddress &host,
                             quint16 port,
                             const std::string &type = "server",
                             QObject *parent = nullptr) : udp_socket(host, port, type, parent) {
}

void client_socket::process(){
    std::vector<std::string> data = parse(queries.front().first);
    std::string status = data[0];
    network::client current_client = queries.front().second;
    queries.pop();
    qDebug() << status.c_str();

    //case for login
    if (status == "allowed"){
        qDebug() << data[1].c_str();
        emit run_successful_login(data[1]);
    }
    if (status == "denied"){
        emit run_wrong_password();
    }
    if (status == "none"){
        emit run_no_user();
    }
    if (status == "dberror"){
        emit run_error();
    }
    //case for registration
    if (status == "created"){
        emit run_successful_registration();
    }
    if (status == "rexists"){
        emit run_duplicate();
    }
    //case for connection
    if (status == "connected"){
        emit run_connect_with_room();
    }
    if (status == "exists"){
    //if (status == "cexists"){
        emit run_already_connected();
    }
}


