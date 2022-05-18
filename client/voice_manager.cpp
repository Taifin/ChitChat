#include "voice_manager.h"
#include <QTimer>

client::processor::processor(network::queries_keeper *keeper1,
                             network::tcp_socket &socket1,
                             QTcpSocket *tcpSocket)
    : query_processor(keeper1, socket1), audio_socket(tcpSocket) {
    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);
    auto info = QAudioDeviceInfo(QAudioDeviceInfo::defaultInputDevice());
    if (!info.isFormatSupported(format))
        format = info.nearestFormat(format);
    audioInput = new QAudioInput(format, this);
    info = QAudioDeviceInfo(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format))
        format = info.nearestFormat(format);
    audioOutput = new QAudioOutput(format, this);
    device = audioOutput->start();
}

void client::processor::process() {
    while (!keeper->parsed_queries.empty()) {
        if (!muted) {
            device->write(keeper->parsed_queries.front().first.data(),
                          keeper->parsed_queries.front().first.size());
        }
        keeper->parsed_queries.pop();
    }
}
void client::processor::input_audio_on() {
    audioInput->start(audio_socket);
    qDebug() << "Microphone is on";
}

void client::processor::input_audio_off() {
    audioInput->stop();
    qDebug() << "Microphone is muted";
}

void client::processor::output_audio_on() {
    muted = false;
    qDebug() << "Headphones are on";
}

void client::processor::output_audio_off() {
    muted = true;
    qDebug() << "Headphones are muted";
}
