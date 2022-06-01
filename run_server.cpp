#include <thread>
#include "server.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    model::database::local_connection();
    auto *keeper = new network::queries_keeper;  // TODO: delete keeper
    auto *audio_keeper = new network::queries_keeper;
#ifdef LOCAL
    server::server_socket receiver(QHostAddress::LocalHost, 1235, keeper);
    server::server_socket audio_receiver(QHostAddress::LocalHost, 1236,
                                         audio_keeper);
#else
    server::server_socket receiver(QHostAddress::Any, 1235, keeper);
    server::server_socket audio_receiver(QHostAddress::Any, 1236, audio_keeper);
#endif
    server::server_processor processor(keeper, receiver);
    server::audio_processor audio(audio_keeper, audio_receiver);
    std::thread t([&processor]() {
        while (true) {
            processor.wait_next_query();
        }
    });
    t.detach();

    std::thread t2([&audio]() {
        while (true) {
            audio.wait_next_query();
        }
    });
    t2.detach();

    return a.exec();
}
