#ifndef GAME_HANGMAN_H
#define GAME_HANGMAN_H

#include <QDebug>
#include <QGridLayout>
#include <QLineEdit>
#include <QPainter>
#include <QScreen>
#include <QToolButton>
#include <QWidget>
#include <map>
#include <random>
#include <vector>
#include "abstract_game.h"

namespace Ui {
class game_hangman;
}

class Q_DECL_EXPORT game_hangman : public ChitChat_game {
    Q_OBJECT

public:
    QPainter painter;
    explicit game_hangman();
    void start() override;
    ~game_hangman() override;
    Ui::game_hangman *ui;

    void get_score() override {
        emit score_sender(score, "hangman");
    }

private:   
    int mistakes;
    std::string used_letters;
    std::string word;
    QToolButton *letters[26];
    bool game_status;
    int score;
    std::string theme;
    std::vector<std::string> themes{"PROGRAMMING", "MATH", "ALGORITHMS"};
    std::map<std::string, std::vector<std::string>> words{
        {"PROGRAMMING", {"templates", "struct", "pointers", "overload"}},
        {"MATH", {"integral", "limit", "graph", "basis"}},
        {"ALGORITHMS", {"tree", "sort", "queue", "binsearch"}}};

protected:
    void paintEvent(QPaintEvent *) override;
    void draw_man(int step);
    void game_start();
    void print_word();
    void win();
    void lose();
    std::string random_word();

private slots:
    void letter_clicked();
};

#endif  // GAME_HANGMAN_H
