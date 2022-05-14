#include "game_selection.h"
#include "QDebug"
#include "ui_game_selection.h"

game_selection::game_selection(QWidget *parent)
    : QWidget(parent), ui(new Ui::game_selection) {
    ui->setupUi(this);
}

game_selection::~game_selection() {
    delete ui;
}

void game_selection::on_hangman_button_clicked() {
    this->hide();
    qDebug() << "HangMan";
}

void game_selection::on_arkanoid_button_clicked() {
    this->hide();
    qDebug() << "Arkanoid";
}

void game_selection::on_back_to_room_button_clicked() {
    this->hide();
}
