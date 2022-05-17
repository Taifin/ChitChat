#include "voice_manager.h"
#include <QTimer>
client::manager::manager(const QHostAddress &host,
                         quint16 port,
                         QTcpSocket *ser,
                         network::queries_keeper *keeper,
                         QObject *parent1)
    : client_socket(host, port, ser,keeper) {
}

QTcpSocket *client::manager::get_socket() {
    return socket;
}

client::processor::processor(network::queries_keeper *keeper1,
                             network::tcp_socket &socket1)
    : query_processor(keeper1, socket1) {
    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);
    audioInput = new QAudioInput(format);
    audioOutput = new QAudioOutput(format);
    device = audioOutput->start();
    qDebug() << "Starting recording";
    audioInput->start(dynamic_cast<client::manager&>(socket).get_socket());
}

void client::processor::process() {
    while (!keeper->parsed_queries.empty()) {
        device->write(keeper->parsed_queries.front().first.data(),
                      keeper->parsed_queries.front().first.size());
        keeper->parsed_queries.pop();
    }
}

