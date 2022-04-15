#include "server.h"
#include <thread>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  model::database::local_connection();
  network::queries_keeper *keeper =
      new network::queries_keeper; // TODO: delete keeper
#ifdef LOCAL
  sv::server_socket receiver(QHostAddress::LocalHost, 1235, keeper);
#else
  sv::server_socket receiver(QHostAddress::Any, 1235, keeper);
#endif
  sv::server_processor processor(keeper, receiver);
  std::thread t([&processor]() {
    while (true) {
      processor.wait_next_query();
    }
  });
  t.detach();

  return a.exec();
}
