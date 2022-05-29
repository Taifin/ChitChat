#include "game_selection.h"
#include <QScreen>
#include "QDebug"
#include "ui_game_selection.h"

game_selection::game_selection(QWidget *parent)
    : QWidget(parent), ui(new Ui::game_selection) {
    ui->setupUi(this);
    connect(this, SIGNAL(game_chosen(const std::string &)), this,
            SLOT(start_game(const std::string &)));
    this->setWindowTitle("ChitChat");
    move(QGuiApplication::screens().at(0)->geometry().center() -
         frameGeometry().center());
    this->raise();
}

game_selection::~game_selection() {
    delete ui;
}

void game_selection::on_hangman_button_clicked() {
    this->close();
    // this->hide();
    qDebug() << "HangMan";
    emit(game_chosen("Hangman"));
}

void game_selection::on_arkanoid_button_clicked() {
    this->close();
    // this->hide();
    qDebug() << "Arkanoid";
    emit(game_chosen("Arkanoid"));
}

void game_selection::on_back_to_room_button_clicked() {
    this->close();
    // this->hide();
}

void game_selection::start_game(const std::string &name) {
    delete game;
    QFileInfo info(name.c_str());
    game = new QLibrary(info.absoluteFilePath());
    if (game->load()) {
        qDebug() << "Loaded!";
        typedef ChitChat_game *(*CreateGame)();
        auto f = (CreateGame)game->resolve("get_game");
        if (f) {
            qDebug() << "Game found!";
            ChitChat_game *w = f();
            w->start();
        }
    } else {
        qDebug() << game->errorString();
    }
}

void game_selection::on_rating_button_clicked() {
    games_rating.update_rating();
    games_rating.show();
    this->close();
}
