#include "sprite.h"
#include <QKeyEvent>

int STEP_SIZE = 5;

sprite::sprite()
{
     //name_display->setPlainText(QString("a"));
     //name_display->setPlainText(QString("aa"));
}

void sprite::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()){
        case Qt::Key_Up:
            change_position(STEP_SIZE, this, directions::UP);
            break;
        case Qt::Key_Down:
            change_position(STEP_SIZE, this, directions::DOWN);
            break;
        case Qt::Key_Left:
            change_position(STEP_SIZE, this, directions::LEFT);
            break;
        case Qt::Key_Right:
            change_position(STEP_SIZE, this, directions::RIGHT);
            break;
    }
}

sprite::~sprite()
{
    delete name_display;
}

void change_position(int step_size, sprite *walker, directions dir)
{
    switch (dir){
        case directions::UP:
            walker->setPos(walker->x(), walker->y()-step_size);
            walker->name_display->setPos(walker->name_display->x(), walker->name_display->y()-step_size);
            break;
        case directions::DOWN:
            walker->setPos(walker->x(), walker->y()+step_size);
            walker->name_display->setPos(walker->name_display->x(), walker->name_display->y()+step_size);
            break;
        case directions::RIGHT:
            walker->setPos(walker->x()+step_size, walker->y());
            walker->name_display->setPos(walker->name_display->x()+step_size, walker->name_display->y());
            break;
        case directions::LEFT:
            walker->setPos(walker->x()-step_size, walker->y());
            walker->name_display->setPos(walker->name_display->x()-step_size, walker->name_display->y());
            break;
    }

}

