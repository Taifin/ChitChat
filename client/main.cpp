#include "main_window.h"

#include <QApplication>
#include "client_socket.h"
#include "socket.h"

#include <map>
#include "client_user.h"

client_socket socket(QHostAddress::AnyIPv4, 60000, nullptr);
//network::client server{QHostAddress("194.169.163.120"), 1235};
network::client server{QHostAddress::LocalHost, 1234};
client_user current_user("noname", "default_password");
std::map<std::string, client_user> users_in_the_room;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    main_window w;
    w.start();

    return a.exec();
}
