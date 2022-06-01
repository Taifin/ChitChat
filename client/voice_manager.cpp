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
    outDevice = audioOutput->start();
}

void client::processor::process() {
    while (keeper->parsed_size() > 0) {
        if (!muted) {
            outDevice->write(keeper->front_parsed().first.data(),
                          keeper->front_parsed().first.size());
        }
        keeper->pop_parsed();
    }
}
void client::processor::input_audio_on() {
    inDevice = audioInput->start();
    connect(inDevice, SIGNAL(bytesWritten()), this, SLOT(send()));
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

void client::processor::send() {
    auto size = inDevice->bytesAvailable();
    qDebug() << "Audio of size" << size << "is being sent";
    QByteArray array(reinterpret_cast<const char*>(&size), 4);
    array.append(inDevice->readAll(), (int)(size));
    audio_socket->write(array);
}
