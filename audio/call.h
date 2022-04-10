#ifndef CALL_H
#define CALL_H

#include <QAudio>
#include <QAudioInput>
#include <QAudioOutput>
#include <QObject>

class Call : public QObject {
    Q_OBJECT
public:
    virtual ~Call();
public slots:
    void onConnected();
};

#endif