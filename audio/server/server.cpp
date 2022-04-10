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
        format.setSampleRate(8000);
        format.setChannelCount(1);
        format.setSampleSize(8);
        format.setCodec("audio/pcm");
        format.setByteOrder(QAudioFormat::LittleEndian);
        format.setSampleType(QAudioFormat::UnSignedInt);
    }

    // m_inputaudio = new QAudioInput(format, this);
    m_outputaudio = new QAudioOutput(format, this);
    std::cerr << "m_outputaudio creatde" << std::endl;

    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(getMusic()));
}
void Server::getMusic() {
    std::cerr << "getMusic" << std::endl;
    // m_inputaudio->start(socket);
    QIODevice *device = m_outputaudio->start();

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