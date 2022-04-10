#include "call.h"
#include <QAudio>
#include <QAudioInput>
#include <QAudioOutput>
#include <QObject>
#include <QUdpSocket>

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

    QUdpSocket *socket = new QUdpSocket();
    // socket->connectToHost("194.169.163.120", 4269);
    m_inputaudio = new QAudioInput(format);
    m_outputaudio = new QAudioOutput(format);

    socket->connectToHost("127.0.0.1", 4269);

    m_inputaudio->start(socket);
}