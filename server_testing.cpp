#include "server.h"
#include <thread>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    model::database::local_connection();
    network::queries_keeper* keeper = new network::queries_keeper;
#ifdef LOCAL
    sv::server_socket receiver(QHostAddress::LocalHost, 60000, keeper);
#else
    sv::server_socket receiver(QHostAddress::Any, 60000, keeper);
#endif
    sv::server_processor processor(keeper, receiver);
    std::thread t([&processor](){
       while (true) {
           processor.wait_next_query();
       }
    });
    t.detach();

    return a.exec();
}