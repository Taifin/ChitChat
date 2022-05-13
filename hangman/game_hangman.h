#ifndef GAME_HANGMAN_H
#define GAME_HANGMAN_H

#include <QWidget>
#include <QPainter>
#include <QToolButton>

namespace Ui {
class game_hangman;
}

class game_hangman : public QWidget
{
    Q_OBJECT

public:
    QPainter painter;
    explicit game_hangman(QWidget *parent = nullptr);
    ~game_hangman();

private:
    Ui::game_hangman *ui;
    int mistakes;
    std::string used_letters;
    std::string word;
    QToolButton* letters[26];
    QToolButton* start_button;
    QToolButton* exit_button;
    bool game_status;
    int score;
    std::string theme;


protected:
    void paintEvent(QPaintEvent*) override;
    void draw_man(int step);
    void game_start();
    void print_letters();
    void print_word();
    void win();
    void lose();
    std::string random_word();

    QToolButton* create_button();

private slots:
    void letter_clicked();
};

#endif // GAME_HANGMAN_H
