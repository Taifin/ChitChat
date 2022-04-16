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
    void setConnection(quint16 port);

public slots:
    void getMusic();

private:
    QUdpSocket *in_socket;
    // QUdpSocket *out_socket;
    // QAudioInput *m_inputaudio;
    // QAudioOutput *m_outputaudio;
    // QIODevice *device;
    // QByteArray data_buffer_1;
    // QByteArray data_buffer_2;
};

#endif