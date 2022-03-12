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
                  const std::string &type,
                  QObject *parent);

    void process();

signals:
    void run_successful_login();

    void run_wrong_password();

    void run_no_user();

    void run_error();

    void run_successful_registration();

    void run_duplicate();

    //void run_error();

private:

};

#endif // CLIENT_SOCKET_H

