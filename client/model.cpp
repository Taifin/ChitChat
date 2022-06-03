#include "model.h"

model::model()
    : socket(QHostAddress::Any, PORT, data_socket, keeper, nullptr),
      a_socket(QHostAddress::Any, PORT, audio_socket, audio_keeper, nullptr),
      processor(keeper, socket),
      audio_processor(audio_keeper, a_socket, audio_socket) {
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
