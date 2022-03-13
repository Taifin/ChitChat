#include "sprite.h"
#include <QKeyEvent>

void sprite::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up){
        setPos(x(), y()-5);
    }
    if (event->key() == Qt::Key_Down){
        setPos(x(), y()+5);
    }
    if (event->key() == Qt::Key_Left){
        setPos(x()-5, y());
    }
    if (event->key() == Qt::Key_Right){
        setPos(x()+5, y());
    }
}
