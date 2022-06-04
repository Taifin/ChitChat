#include "rating.h"
#include "ui_rating.h"

rating::rating(QWidget *parent) : QWidget(parent), ui(new Ui::rating) {
    ui->setupUi(this);
}

rating::~rating() {
    delete ui;
}

void rating::on_back_to_room_button_clicked() {
    this->hide();
}

void rating::update_rating() {
    sort(hangman_rating.begin(), hangman_rating.end());
    sort(arkanoid_rating.begin(), arkanoid_rating.end());
    std::string hangman_names = "";
    std::string hangman_scores = "";
    std::string arkanoid_names = "";
    std::string arkanoid_scores = "";

    for (auto &x : hangman_rating) {
        hangman_names += x.second + "\n";
        hangman_scores += std::to_string(x.first) + "\n";
    }

    for (auto &x : arkanoid_rating) {
        arkanoid_names += x.second + "\n";
        arkanoid_scores += std::to_string(x.first) + "\n";
    }

    ui->arkanoid_names->setText(arkanoid_names.c_str());
    ui->arkanoid_score->setText(arkanoid_scores.c_str());
    ui->hangman_names->setText(hangman_names.c_str());
    ui->hangman_score->setText(hangman_scores.c_str());
}
