#include "include/Platform.h"

void Plank::change_pos(int step, int direction) {
    this->setPos(this->x() + direction * step, this->y());
}

void Plank::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Left:
            if (this->x() - 10 >= -250)
                change_pos(10, -1);
            break;
        case Qt::Key_Right:
            if (this->x() + 10 <= 250)
                change_pos(10, 1);
            break;
    }
}