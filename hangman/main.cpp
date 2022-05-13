#include <QApplication>
#include "game_hangman.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    game_hangman g;
    g.show();
    return a.exec();
}
