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
#include <queue>
#include "user.h"

namespace sv {
struct sender {
    QHostAddress address;
    int port;
};

class controller : public QObject {
    Q_OBJECT
private:
    enum class e_commands{
        LOGIN, REGISTER, CONNECT, GREET
    };
    std::map<std::string, e_commands> commands{
        {"login", e_commands::LOGIN},
        {"register", e_commands::REGISTER},
        {"connect", e_commands::CONNECT},
        {"hello", e_commands::GREET}
    };

    std::queue<std::pair<std::string, sv::sender>> queries;

//    std::map<std::string, User> server_users;
//    static std::pair<std::string, User> create_user(
//        const std::string &user_data,
//        const QHostAddress &address,
//        int port);

public:
    explicit controller(const QHostAddress &host = QHostAddress::LocalHost,
                    qint16 port = 7755,
                    QObject *parent = nullptr);

    std::vector<std::string> parse(const std::string &data);

    void process();

    void login_placeholder() {};

    void register_placeholder() {};

    void connect_placeholder() {};

    void greet(std::vector<std::string> &data, const sv::sender& to);

//    bool connect_user(const std::string &user_data,
//                      const QHostAddress &address,
//                      int port);

    virtual ~controller(){};

signals:

public slots:
    void readPendingDatagrams();

private:
    QUdpSocket *server_socket;
};
}  // namespace sv
#endif