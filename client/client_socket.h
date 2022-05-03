#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <QObject>
#include <QString>
#include <QUdpSocket>
#include "shared/socket.h"

class client_socket : public network::tcp_socket {
    Q_OBJECT
public:
    client_socket(const QHostAddress &host,
                  quint16 port,
                  QTcpSocket *ser,
                  network::queries_keeper *keeper,
                  QObject *parent);
signals:
};

class client_processor : public network::query_processor {
    Q_OBJECT;

public:
    client_processor(network::queries_keeper *keeper,
                     network::tcp_socket &socket)
        : network::query_processor(keeper, socket) {
    }
    void process() override;

signals:
    void run_successful_login(const std::string &name);

    void run_wrong_password();

    void run_no_user();

    void run_error();

    void run_successful_registration();

    void run_duplicate();

    void run_already_connected();

    void run_connect_with_room(std::vector<std::string> data);

    void run_move(std::string username, int x, int y);

    void run_get();

    void run_change_position(std::string, int, int);

    void run_disconnect_roommate(const std::string &);

    void run_connect_roommate(const std::string &);

};

#endif  // CLIENT_SOCKET_H
