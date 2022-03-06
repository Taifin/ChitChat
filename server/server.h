#ifndef CHITCHAT_SERVER_H
#define CHITCHAT_SERVER_H

#include <QCoreApplication>
#include <QNetworkDatagram>
#include <QObject>
#include <QUdpSocket>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "entities/user.h"

namespace sv {
struct server : public QObject {
    Q_OBJECT
private:
    std::map<std::string, User> server_users;

    static std::pair<std::string, User> create_user(
        const std::string &user_data,
        const QHostAddress &address,
        int port);

public:
    explicit server(const QHostAddress &host = QHostAddress::LocalHost,
                    qint16 port = 7755,
                    QObject *parent = nullptr);

    bool connect_user(const std::string &user_data,
                      const QHostAddress &address,
                      int port);

    virtual ~server(){};

signals:

public slots:
    void readPendingDatagrams();

private:
    QUdpSocket *server_socket;
};
}  // namespace sv
#endif