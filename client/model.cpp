#include "model.h"

model::model()
    : socket(QHostAddress::Any, PORT, remote_server, keeper, nullptr),
      processor(keeper, socket) {
    remote_server->connectToHost(QHostAddress("194.169.163.120"), 1235);
}

void model::send_request(const std::string &message) {
    processor.prepare_query(message, remote_server);
}

model::~model() {
    delete keeper;
    delete remote_server;
}
