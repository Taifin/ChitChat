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
#include <thread>

QByteArray data_buffer_1;

Server::~Server() {
}

void Server::setConnection(quint16 port) {
    in_socket = new QUdpSocket();
    in_socket->bind(QHostAddress::Any, port);

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
    QUdpSocket *from = in_socket;
    std::cerr << "getMusic" << std::endl;
    // m_inputaudio->start(in_socket);

    while (from->hasPendingDatagrams()) {
        std::cerr << "hasPendingDatagrams() == true" << std::endl;
        // QByteArray data_buffer_1;
        data_buffer_1.resize(in_socket->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        from->readDatagram(data_buffer_1.data(), data_buffer_1.size(), &sender,
                           &senderPort);
        from->writeDatagram(data_buffer_1, sender, senderPort);
        data_buffer_1.clear();
    }
}

void thread_connection(Server *server, qint16 port) {
    server->setConnection(port);
}
int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);

    Server server;
    Server server2;

    qint16 port_1, port_2;

    std::cin >> port_1 >> port_2;
    std::cout << "F" << std::endl;
    
    // std::thread first(thread_connection, &server, port_1);
    // std::thread second(thread_connection, &server2, port_2);
    // std::thread first(thread_connection, &server, port_1);
    server.setConnection(port_1);
    // first.detach();
    // second.detach();

    server2.setConnection(port_2);
//	while(true){
		
//	}
   return app.exec();
}
