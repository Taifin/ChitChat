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
    virtual ~Call();
public slots:
    void onConnected();

private:
    QAudioInput *m_inputaudio;
    QAudioOutput *m_outputaudio;
};

#endif