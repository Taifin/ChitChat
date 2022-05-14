#ifndef ROOM_H
#define ROOM_H
#include <QGraphicsScene>
#include <QKeyEvent>
#include "game_selection.h"
#include "sprite.h"

class room : public QGraphicsScene {
public:
    room();
    void keyPressEvent(QKeyEvent *event) override;
    void set_curren_user_sprite(sprite *spr);
    sprite_of_object *game_machine = new sprite_of_object("game_machine");

private:
    sprite *current_user_sprite;
    game_selection choose_game;
};

#endif  // ROOM_H
