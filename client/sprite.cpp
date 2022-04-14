#include "sprite.h"
#include "client_socket.h"
#include <QKeyEvent>

int STEP_SIZE = 5;

extern network::client server;
extern client_socket socket;


sprite::sprite(std::string name) : name(name)
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
    int x = walker->x();
    int y = walker->y();
    switch (dir){
        case directions::UP:
            socket.send_datagram("move," + walker->name + "," + std::to_string(x) + "," + std::to_string(y-step_size), server);
            walker->setPos(x, y-step_size);
            walker->name_display->setPos(walker->name_display->x(), walker->name_display->y()-step_size);
            break;
        case directions::DOWN:
            socket.send_datagram("move," + walker->name + "," + std::to_string(x) + "," + std::to_string(y+step_size), server);
            walker->setPos(x, y+step_size);
            walker->name_display->setPos(walker->name_display->x(), walker->name_display->y()+step_size);
            break;
        case directions::RIGHT:
            socket.send_datagram("move," + walker->name + "," + std::to_string(x+step_size) + "," + std::to_string(y), server);
            walker->setPos(x+step_size, y);
            walker->name_display->setPos(walker->name_display->x()+step_size, walker->name_display->y());
            break;
        case directions::LEFT:
            socket.send_datagram("move," + walker->name + "," + std::to_string(x-step_size) + "," + std::to_string(y), server);
            walker->setPos(x-step_size, y);
            walker->name_display->setPos(walker->name_display->x()-step_size, walker->name_display->y());
            break;
    }

}
