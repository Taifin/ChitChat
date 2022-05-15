#include "voice_manager.h"
#include <QFile>
#include <QTimer>
void client::manager::read() {
    qDebug() << "Received";
    auto *sender = dynamic_cast<QTcpSocket *>(QObject::sender());
    QByteArray data = sender->readAll();
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultOutputDevice();
    qDebug() << data.size();
    device->write(data.data(), data.size());
//    std::unique_lock lock(keeper->queries_mutex);
//    keeper->parsed_queries.push({data, sender});
//    keeper->query_available.notify_one();
}
client::manager::manager(const QHostAddress &host,
                         quint16 port,
//                         network::queries_keeper<QByteArray> *keeper,
                         QObject *parent) {
    socket = new QTcpSocket(this);
    socket->connectToHost(host, port);
    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);
    audioOutput = new QAudioOutput(format);
    device = audioOutput->start();
//    this->keeper = keeper;
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
}
QTcpSocket *client::manager::get_socket() {
    return socket;
}

client::processor::processor(client::manager& socket) : socket(socket) {
//    d.setFileName("aboba.wav");
//    d.open(QIODevice::WriteOnly);
    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);
    audioInput = new QAudioInput(format);
//    audioOutput = new QAudioOutput(format);
    qDebug() << "Starting recording";
    audioInput->start(socket.get_socket());
//    audioInput->start(&d);
//    QTimer::singleShot(3000, this, SLOT(stopAudio()));
}

//void client::processor::wait_next_query() {
//    std::unique_lock lock(keeper->queries_mutex);
//    keeper->query_available.wait(
//        lock, [&]() { return !keeper->parsed_queries.empty(); });
//    process();
//}

//void client::processor::process() {
//    while (!keeper->parsed_queries.empty()) {
//        device->write(keeper->parsed_queries.front().first.data(),
//                      keeper->parsed_queries.front().first.size());
//        keeper->parsed_queries.pop();
//    }
//}

//void client::processor::prepare_query(const QByteArray &q, QTcpSocket *cli) {
//    keeper->prepared_queries.push({q, cli});
//    emit prepared();
//}

void client::processor::stopAudio() {
    audioInput->stop();
    delete audioInput;
//    d.close();
    qDebug() << "Recording stopped";
}
