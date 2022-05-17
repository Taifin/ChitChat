#include "QApplication"
#include "client/voice_manager.h"
#include "thread"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto *keeper = new network::queries_keeper();
    auto *socket = new QTcpSocket();
    socket->connectToHost(QHostAddress("194.169.163.120"), 1236);
    client_socket m(QHostAddress("194.169.163.120"), 1236, socket, keeper, nullptr);

    client::processor processor(keeper, m, socket);
    std::thread t([&processor]() {
        while (true) {
            processor.wait_next_query();
        }
    });
    t.detach();

    return a.exec();
}