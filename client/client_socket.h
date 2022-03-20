#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <QString>
#include <QUdpSocket>
#include <QObject>
#include "socket.h"

class client_socket : public network::udp_socket
{
    Q_OBJECT
public:
    client_socket(const QHostAddress &host,
                  quint16 port,
                  const std::string &type ,
                  QObject *parent);

    void process();

signals:
    void run_successful_login(std::string name);

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

    //void run_initialize_users_in_the_room(std::vector<std::string> data);
};

#endif // CLIENT_SOCKET_H

