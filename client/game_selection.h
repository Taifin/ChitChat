#ifndef GAME_SELECTION_H
#define GAME_SELECTION_H

#include <QDebug>
#include <QWidget>
#include "QFileInfo"
#include "QLibrary"
#include "abstract_game.h"
#include "rating.h"

namespace Ui {
class game_selection;
}

class Q_DECL_IMPORT game_selection : public QWidget {
    Q_OBJECT

public:
    explicit game_selection(QWidget *parent = nullptr);

    ~game_selection() override;

private slots:
    void on_rating_button_clicked();

private slots:
    void on_back_to_room_button_clicked();
    void on_arkanoid_button_clicked();
    void on_hangman_button_clicked();

    void start_game(const std::string &name);

    void send_score(int score, const std::string& game_name);

signals:
    void game_chosen(const std::string &name);

    void run_send_score(int, std::string);

private:
    Ui::game_selection *ui;
    QLibrary *game = nullptr;
    rating games_rating;
};

#endif  // GAME_SELECTION_H
