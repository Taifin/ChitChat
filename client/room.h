#ifndef ROOM_H
#define ROOM_H
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTime>
#include <QTimer>
#include "QTimer"
#include "game_selection.h"
#include "sprite.h"

static int TIME_TO_GO = 43;

class room : public QGraphicsScene {
    Q_OBJECT
public:
    room();
    void keyPressEvent(QKeyEvent *event) override;
    void set_curren_user_sprite(sprite *spr);
    sprite_of_object *game_machine;

    void set_game_machine();

    void dont_let_to_move();

    QGraphicsTextItem *text = new QGraphicsTextItem();
    game_selection choose_game;

public slots:
    void let_to_move();

private:
    sprite *current_user_sprite;
    bool can_move = true;

    QTimer *timer;
};

#endif  // ROOM_H
