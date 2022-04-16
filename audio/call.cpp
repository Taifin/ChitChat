#include "call.h"
#include <QAudio>
#include <QAudioInput>
#include <QAudioOutput>
#include <QObject>
#include <QUdpSocket>
#include <iostream>
Call::~Call() {
}

void Call::onConnected() {
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

    // QUdpSocket *out_socket = new QUdpSocket();
    // out_socket->connectToHost("127.0.0.1", 4242);

    first_socket = new QUdpSocket();
    first_socket->connectToHost("127.0.0.1", 4242);

    m_inputaudio = new QAudioInput(format);
    m_outputaudio = new QAudioOutput(format);

    m_inputaudio->start(first_socket);

    device = m_outputaudio->start();

    std::cerr << "device created" << std::endl;
    // QObject::connect(first_socket, SIGNAL(readyRead()), this,
    // SLOT(getMusic()));
    first_socket->connect(first_socket, SIGNAL(readyRead()), this,
                          SLOT(getMusic()));
}

void Call::getMusic() {
    std::cerr << "Call::getMusic()" << std::endl;
    while (first_socket->hasPendingDatagrams()) {
        std::cerr << "data recieved" << std::endl;
        QByteArray data;
        data.resize(first_socket->pendingDatagramSize());
        first_socket->readDatagram(data.data(), data.size());
        device->write(data.data(), data.size());
    }
}