#ifndef ROOM_H
#define ROOM_H
#include <QGraphicsScene>
#include <QKeyEvent>
#include "sprite.h"

class room : public QGraphicsScene {
public:
    room();
    void keyPressEvent(QKeyEvent *event) override;
    void set_curren_user_sprite(sprite *spr);

private:
    sprite *current_user_sprite;
};

#endif  // ROOM_H
