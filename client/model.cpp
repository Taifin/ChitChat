#include "model.h"

model::model()
    : socket(QHostAddress::Any, PORT, data_socket, keeper, nullptr),
      processor(keeper, socket),
      audio_processor(keeper, socket, audio_socket) {
#ifndef LOCAL
    data_socket->connectToHost(QHostAddress("194.169.163.120"), PORT);
    audio_socket->connectToHost(QHostAddress("194.169.163.120"), PORT + 1);
#else
    data_socket->connectToHost(QHostAddress::LocalHost, PORT);
    audio_socket->connectToHost(QHostAddress::LocalHost, PORT + 1);
#endif
}

void model::send_request(const ChitChatMessage::Query &message) {
    processor.prepare_query(message, data_socket);
}

model::~model() {
    delete keeper;
    delete data_socket;
}
