#include "model.h"

model::model()
    : socket(QHostAddress::Any, PORT, remote_server, keeper, nullptr),
      processor(keeper, socket) {
#ifndef LOCAL
    remote_server->connectToHost(QHostAddress("194.169.163.120"), 1235);
#else
    remote_server->connectToHost(QHostAddress::LocalHost, 1235);
#endif
}

void model::send_request(const std::string &message) {
    qDebug() << message.c_str();
    processor.prepare_query(message, remote_server);
}

model::~model() {
    delete keeper;
    delete remote_server;
}
