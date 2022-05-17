#include "voice_manager.h"
#include <QTimer>

client::processor::processor(network::queries_keeper *keeper1,
                             network::tcp_socket &socket1, QTcpSocket* tcpSocket)
    : query_processor(keeper1, socket1) {
    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);
    auto info = QAudioDeviceInfo(QAudioDeviceInfo::defaultInputDevice());
    if (!info.isFormatSupported(format)) format = info.nearestFormat(format);
    audioInput = new QAudioInput(format);
    info = QAudioDeviceInfo(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) format = info.nearestFormat(format);
    audioOutput = new QAudioOutput(format);
    device = audioOutput->start();
    qDebug() << "Starting recording";
    qDebug() << info.isFormatSupported(format);
    audioInput->start(tcpSocket);
}

void client::processor::process() {
    while (!keeper->parsed_queries.empty()) {
        device->write(keeper->parsed_queries.front().first.data(),
                      keeper->parsed_queries.front().first.size());
        keeper->parsed_queries.pop();
    }
}

