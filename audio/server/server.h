#ifndef SERVER_H
#define SERVER_H
#include <QObject>
#include <QUdpSocket>
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioInput>
#include <QtMultimedia/QAudioOutput>

class Server : public QObject {
    Q_OBJECT
public:
    virtual ~Server();
    Server();
    void start() {
        // listen(QHostAddress::Any, 4269);
    }

public slots:
    void getMusic();

private:
    QUdpSocket *socket;
    QAudioInput *m_inputaudio;
    QAudioOutput *m_outputaudio;
    QIODevice *device;
};
#endif