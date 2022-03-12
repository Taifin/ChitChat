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
    qDebug() << queries.size();

    //case for login
    if (status == "allowed"){
        emit run_successful_login();
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
    if (status == "exists"){
        emit run_duplicate();
    }

}

