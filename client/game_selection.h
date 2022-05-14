#ifndef GAME_SELECTION_H
#define GAME_SELECTION_H

#include <QWidget>

namespace Ui {
class game_selection;
}

class game_selection : public QWidget {
    Q_OBJECT

public:
    explicit game_selection(QWidget *parent = nullptr);

    ~game_selection();

private slots:
    void on_back_to_room_button_clicked();

private slots:
    void on_arkanoid_button_clicked();

private slots:
    void on_hangman_button_clicked();

private:
    Ui::game_selection *ui;
};

#endif  // GAME_SELECTION_H
