#include "server/voice_manager.h"
#include "QApplication"
#include "thread"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    auto *keeper = new network::queries_keeper<QByteArray>();
    server::manager m(QHostAddress::LocalHost, 1234, keeper);

    server::processor processor(m, keeper);
    std::thread t([&processor]() {
        while (true) {
            processor.wait_next_query();
        }
    });
    t.detach();

    return a.exec();
}