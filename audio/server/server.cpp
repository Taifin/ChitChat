#include "server.h"
#include <QApplication>
#include <QObject>
#include <QUdpSocket>
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioInput>
#include <QtMultimedia/QAudioOutput>
#include <iostream>

Server::~Server() {
}

Server::Server() {
    socket = new QUdpSocket();
    socket->bind(4269);

    QAudioFormat format;
    {
        format.setSampleRate(128000);
        format.setChannelCount(1);
        format.setSampleSize(16);
        format.setCodec("audio/pcm");
        format.setByteOrder(QAudioFormat::LittleEndian);
        format.setSampleType(QAudioFormat::UnSignedInt);
    }

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format))
        format = info.nearestFormat(format);

    // m_inputaudio = new QAudioInput(format);
    // m_inputaudio->start(socket);

    m_outputaudio = new QAudioOutput(format);
    std::cerr << "m_outputaudio creatde" << std::endl;
    device = m_outputaudio->start();

    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(getMusic()));
}
void Server::getMusic() {
    std::cerr << "getMusic" << std::endl;
    // m_inputaudio->start(socket);

    while (socket->hasPendingDatagrams()) {
        QByteArray data;
        data.resize(socket->pendingDatagramSize());
        socket->readDatagram(data.data(), data.size());
        device->write(data.data(), data.size());
    }
}
int main(int argc, char **argv) {
    QApplication app(argc, argv);
    Server server;
    // server.start();
    return app.exec();
}