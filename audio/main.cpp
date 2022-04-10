#include <QApplication>
#include <QAudio>
#include <QAudioInput>
#include <QAudioOutput>
#include <QObject>
#include "call.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    Call call;
    call.onConnected();
    return app.exec();
}