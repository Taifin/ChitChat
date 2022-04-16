#ifndef CALL_H
#define CALL_H

#include <QAudio>
#include <QAudioInput>
#include <QAudioOutput>
#include <QObject>
#include <QUdpSocket>
class Call : public QObject {
    Q_OBJECT
public:
    quint16 port = 4242;
    virtual ~Call();
public slots:
    void onConnected();
    void getMusic();

private:
    QAudioInput *m_inputaudio;
    QAudioOutput *m_outputaudio;
    QUdpSocket *first_socket;
    QIODevice *device;
};

#endif