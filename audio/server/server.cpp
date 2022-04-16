#include "server.h"
#include <QApplication>
#include <QHostAddress>
#include <QNetworkDatagram>
#include <QObject>
#include <QString>
#include <QUdpSocket>
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioInput>
#include <QtMultimedia/QAudioOutput>
#include <iostream>

Server::~Server() {
}

Server::Server() {
    in_socket = new QUdpSocket();
    in_socket->bind(4242);

    // out_socket = new QUdpSocket();
    // out_socket->bind(4141);

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

    // m_outputaudio = new QAudioOutput(format);
    // std::cerr << "m_outputaudio creatde" << std::endl;
    // device = m_outputaudio->start();

    QObject::connect(in_socket, SIGNAL(readyRead()), this, SLOT(getMusic()));
}
void Server::getMusic() {
    std::cerr << "getMusic" << std::endl;
    // m_inputaudio->start(in_socket);

    while (in_socket->hasPendingDatagrams()) {
        std::cerr << "hasPendingDatagrams() == true" << std::endl;
        QByteArray data;
        data.resize(in_socket->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;
        // in_socket->readDatagram(data.data(), data.size());
        in_socket->readDatagram(data.data(), data.size(), &sender, &senderPort);
        // device->write(data.data(), data.size());

        // QNetworkDatagram datagram =
        //->receiveDatagram(100);

        // std::cerr << "data recived" << std::endl
        //           <<
        //           datagram.destinationAddress().toString().toStdString()
        //           << std::endl;
        //     auto otherAddress = datagram.senderAddress();
        // auto otherPort = datagram.senderPort();
        // datagram.setSender(datagram.destinationAddress(),
        //                    datagram.destinationPort());
        // datagram.setDestination(otherAddress, otherPort);
        in_socket->writeDatagram(data, sender, senderPort);
    }
}
int main(int argc, char **argv) {
    QApplication app(argc, argv);
    Server server;
    // server.start();
    return app.exec();
}