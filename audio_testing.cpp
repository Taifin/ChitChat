#include "QApplication"
#include "client/voice_manager.h"
#include "thread"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto *keeper = new network::queries_keeper<QByteArray>();
    client::manager m(<#initializer #>, 0, nullptr, nullptr, nullptr,
                      QHostAddress::LocalHost, 1234, keeper, nullptr);

    client::processor processor(nullptr, <#initializer #>, m, keeper);
    std::thread t([&processor]() {
        while (true) {
            processor.wait_next_query();
        }
    });
    t.detach();

    return a.exec();
}