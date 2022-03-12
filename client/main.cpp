#include "main_window.h"
#include "database.h"

#include <QApplication>
#include "client_socket.h"
#include "socket.h"

client_socket socket(QHostAddress::Any, 60000, "", nullptr);
network::client server{QHostAddress("194.169.163.120"), 1235};

int main(int argc, char *argv[])
{
    db::chitchat_database::local_connection();
    db::chitchat_database::debug_create_table();

    QApplication a(argc, argv);
    main_window w;
    w.start();

    return a.exec();
}
