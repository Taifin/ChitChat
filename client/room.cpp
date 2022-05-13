#include "room.h"

room::room() : QGraphicsScene()
{

}

void room::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Up:
            if (this->current_user_sprite->pos().y() > 0){
                change_position(STEP_SIZE, this->current_user_sprite, directions::UP);
            }
            break;
        case Qt::Key_Down:
            if (this->current_user_sprite->pos().y() < 475){
                change_position(STEP_SIZE, this->current_user_sprite, directions::DOWN);
            }
            break;
        case Qt::Key_Left:
            if (this->current_user_sprite->pos().x() > 0){
                change_position(STEP_SIZE, this->current_user_sprite, directions::LEFT);
            }
            break;
        case Qt::Key_Right:
            if (this->current_user_sprite->pos().x() < 525){
                change_position(STEP_SIZE, this->current_user_sprite, directions::RIGHT);
            }
            break;
    }
}

void room::set_curren_user_sprite(sprite *spr){
    current_user_sprite = spr;
}


