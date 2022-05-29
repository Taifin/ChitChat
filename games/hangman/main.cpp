#include <QApplication>
#include "game_hangman.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    game_hangman g;
    g.show();
    return a.exec();
}
