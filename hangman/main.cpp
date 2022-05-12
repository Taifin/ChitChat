#include "mainwindow.h"
#include "game_hangman.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    game_hangman g;
    g.show();
    return a.exec();
}
