#include "main_window.h"
#include "database.h"

#include <QApplication>
#include "client_socket.h"
#include "socket.h"

client_socket socket(QHostAddress::Any, 60000, "", nullptr);
network::client server{QHostAddress("194.169.163.120"), 1235};
user current_user("noname", "amogus");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    main_window w;
    w.start();

    return a.exec();
}
