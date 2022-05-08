#include "sprite.h"
#include <QKeyEvent>
#include <QGraphicsEffect>
#include "client_socket.h"
#include "client_user.h"

int STEP_SIZE = 5;

extern QTcpSocket *remote_server;
extern client_processor processor;
extern client_user current_user;

sprite::sprite(const std::string &name, std::string skin) : name(name) {

    setPixmap(QPixmap(":/images/"+ QString(skin.c_str()) + "_sprite.png"));
    // name_display->setPlainText(QString("a"));
    // name_display->setPlainText(QString("aa"));
}

void sprite::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Up:
            if (pos().y() > -5){
                change_position(STEP_SIZE, this, directions::UP);
            }
            break;
        case Qt::Key_Down:
            if (pos().y() < 455){
                change_position(STEP_SIZE, this, directions::DOWN);
            }
            break;
        case Qt::Key_Left:
            if (pos().x() > -45){
                change_position(STEP_SIZE, this, directions::LEFT);
            }
            break;
        case Qt::Key_Right:
            if (pos().x() < 490){
                change_position(STEP_SIZE, this, directions::RIGHT);
            }
            break;
    }
}

sprite::~sprite() {
    delete name_display;
}

void sprite::change_skin(const std::string &skin)
{
    setPixmap(QPixmap(":/images/"+ QString(skin.c_str()) + "_sprite.png"));
}

void change_position(int step_size, sprite *walker, directions dir) {
    int x = walker->x();
    int y = walker->y();
    switch (dir) {
        case directions::UP:
            processor.prepare_query("move," + walker->name + "," +
                                        std::to_string(x) + "," +
                                        std::to_string(y - step_size),
                                    remote_server);
            walker->setPos(x, y - step_size);
            walker->name_display->setPos(walker->name_display->x(),
                                         walker->name_display->y() - step_size);
            break;
        case directions::DOWN:
            processor.prepare_query("move," + walker->name + "," +
                                        std::to_string(x) + "," +
                                        std::to_string(y + step_size),
                                    remote_server);
            walker->setPos(x, y + step_size);
            walker->name_display->setPos(walker->name_display->x(),
                                         walker->name_display->y() + step_size);
            break;
        case directions::RIGHT:
            processor.prepare_query("move," + walker->name + "," +
                                        std::to_string(x + step_size) + "," +
                                        std::to_string(y),
                                    remote_server);
            walker->setPos(x + step_size, y);
            walker->name_display->setPos(walker->name_display->x() + step_size,
                                         walker->name_display->y());
            break;
        case directions::LEFT:
            processor.prepare_query("move," + walker->name + "," +
                                        std::to_string(x - step_size) + "," +
                                        std::to_string(y),
                                    remote_server);
            walker->setPos(x - step_size, y);
            walker->name_display->setPos(walker->name_display->x() - step_size,
                                         walker->name_display->y());
            break;
    }
    qDebug() << std::to_string(walker->x()).c_str() << std::to_string(walker->y()).c_str();
}

sprite_for_choice::sprite_for_choice(const std::string &skin) : skin(skin)
{
    setPixmap(QPixmap(":/images/"+ QString(skin.c_str()) + "_sprite.png"));
}

void sprite_for_choice::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "cliced" << skin.c_str();
    current_user.skin = skin;
    QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect(this);
    effect->setColor(Qt::black);
    setGraphicsEffect(effect);
    clean_scene_after_choice();
    //setGraphicsEffect(NULL);
}
