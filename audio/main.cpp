#include <QApplication>
#include <QAudio>
#include <QAudioInput>
#include <QAudioOutput>
#include <QObject>
#include <iostream>
#include "call.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    Call call;
    std::cin >> call.port;
    call.onConnected();

    return app.exec();
}