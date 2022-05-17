#include "server/server.h"
#include "QApplication"
#include "thread"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    auto *keeper = new network::queries_keeper();
    sv::server_socket m(QHostAddress::LocalHost, 1234, keeper);

    sv::audio_processor processor(keeper, m);
    std::thread t([&processor]() {
        while (true) {
            processor.wait_next_query();
        }
    });
    t.detach();

    return a.exec();
}