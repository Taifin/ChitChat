#include "room.h"

room::room() : QGraphicsScene() {
    timer = new QTimer();
    this->addItem(text);
    text->hide();
    connect(timer, SIGNAL(timeout()), this, SLOT(let_to_move()));
}

void room::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_G: {
            if (event->modifiers() == Qt::ControlModifier) {
                qDebug() << "cntl+g";
                QList<QGraphicsItem *> colliding_items =
                    current_user_sprite->collidingItems();
                qDebug() << colliding_items.size();
                for (auto &colliding_item : colliding_items) {
                    qDebug() << typeid(sprite_of_object).name();
                    if (colliding_item == game_machine) {
                        choose_game.show();
                        choose_game.activateWindow();
                    }
                }
            }
        } break;
        case Qt::Key_Up:
            if (can_move && this->current_user_sprite->pos().y() > 0) {
                dont_let_to_move();
                change_position(STEP_SIZE, this->current_user_sprite,
                                directions::UP);
            }
            break;
        case Qt::Key_Down:
            if (can_move && this->current_user_sprite->pos().y() < BORDER_Y) {
                dont_let_to_move();
                change_position(STEP_SIZE, this->current_user_sprite,
                                directions::DOWN);
            }
            break;
        case Qt::Key_Left:
            if (can_move && this->current_user_sprite->pos().x() > 0) {
                dont_let_to_move();
                change_position(STEP_SIZE, this->current_user_sprite,
                                directions::LEFT);
            }
            break;
        case Qt::Key_Right:
            if (can_move && this->current_user_sprite->pos().x() < BORDER_X) {
                dont_let_to_move();
                change_position(STEP_SIZE, this->current_user_sprite,
                                directions::RIGHT);
            }
            break;
    }
}

void room::set_curren_user_sprite(sprite *spr) {
    current_user_sprite = spr;
}

void room::set_game_machine() {
    game_machine = new sprite_of_object("game_machine");
}

void room::dont_let_to_move() {
    can_move = false;
    timer->start(TIME_TO_GO);
}

void room::let_to_move() {
    can_move = true;
}
