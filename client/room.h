#ifndef ROOM_H
#define ROOM_H
#include <QGraphicsScene>
#include <QKeyEvent>
#include "game_selection.h"
#include "sprite.h"
#include "QTimer"
#include <QTimer>
#include <QTime>

static int TIME_TO_GO = 10;

class room : public QGraphicsScene {
public:
    room();
    void keyPressEvent(QKeyEvent *event) override;
    void set_curren_user_sprite(sprite *spr);
    sprite_of_object *game_machine = new sprite_of_object("game_machine");

    void dont_let_to_move(){
        timer->start(TIME_TO_GO);
        can_move = false;
    }

private slots:
    void let_to_move(){
        can_move = true;
    }

private:
    sprite *current_user_sprite;
    game_selection choose_game;
    bool can_move = true;
    QTimer *timer = new QTimer();
};

#endif  // ROOM_H
