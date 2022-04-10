#include "server.h"
#include <thread>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    // server's running on localhost, sending to port 50000, listening on port 60000

    model::database::local_connection();
    network::queries_keeper* keeper = new network::queries_keeper;
    sv::server_socket receiver(QHostAddress::LocalHost, 60000, keeper);
    sv::server_socket sender(QHostAddress::LocalHost, 0, keeper);
    sv::server_processor processor(keeper, sender);
    std::thread t([&processor](){
       while (true) {
           processor.wait_next_query();
       }
    });
    t.detach();

    return a.exec();
}