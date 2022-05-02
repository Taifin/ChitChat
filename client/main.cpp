#include <QApplication>
#include <map>
#include <thread>
#include "client_socket.h"
#include "client_user.h"
#include "main_window.h"
#include "socket.h"


QTcpSocket *remote_server = new QTcpSocket();
client_user current_user("noname", "default_password");
std::map<std::string, client_user> users_in_the_room;
network::queries_keeper *keeper =
    new network::queries_keeper;  //Нужно delete keeper;

client_socket socket(QHostAddress::Any, 60000, remote_server, keeper, nullptr);
client_processor processor(keeper, socket);

int main(int argc, char *argv[]) {
    std::thread t([]() {
      while (true) {
        processor.wait_next_query();
      }
    });
    t.detach();

    QApplication a(argc, argv);
    main_window w;
    w.start();

    return a.exec();
}
