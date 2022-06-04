#include "sprite.h"
#include "client_socket.h"
#include "view.h"

sprite::sprite(const std::string &name, const std::string &skin) : name(name) {
    setPixmap(QPixmap(":/images/" + QString(skin.c_str()) + "_sprite.png"));
    QPen pen;

    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);
    pen.setBrush(Qt::white);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setColor(Qt::black);

    QFont font("Source Code Pro", 12);
    name_display->setFont(font);
    name_display->setPos(SPRITE_SIZE_X, SPRITE_SIZE_Y);
    name_display->setPen(pen);
}

void sprite::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Up:
            if (pos().y() > 0) {
                change_position(STEP_SIZE, this, directions::UP);
            }
            break;
        case Qt::Key_Down:
            if (pos().y() < BORDER_Y) {
                change_position(STEP_SIZE, this, directions::DOWN);
            }
            break;
        case Qt::Key_Left:
            if (pos().x() > 0) {
                change_position(STEP_SIZE, this, directions::LEFT);
            }
            break;
        case Qt::Key_Right:
            if (pos().x() < BORDER_X) {
                change_position(STEP_SIZE, this, directions::RIGHT);
            }
            break;
    }
}

sprite::~sprite() {
    delete name_display;
}

void sprite::change_skin(const std::string &skin) {
    setPixmap(QPixmap(":/images/" + QString(skin.c_str()) + "_sprite.png"));
}

bool sprite::is_colliding() {
    QGraphicsScene *scene = this->scene();
    QList<QGraphicsItem *> colliding_items = this->collidingItems();
    for (auto &colliding_item : colliding_items) {
        if (typeid(*colliding_item) == typeid(sprite_of_object)) {
            auto *effect = new QGraphicsColorizeEffect();
            effect->setColor(Qt::black);
            colliding_item->setGraphicsEffect(effect);

            (dynamic_cast<sprite_of_object *>(colliding_item))
                ->set_text("Press CTRL+G to start a game");
            scene->addItem(
                (dynamic_cast<sprite_of_object *>(colliding_item))->text);
            return true;
        } else {
            colliding_item->setGraphicsEffect(nullptr);
        }
    }
    QList<QGraphicsItem *> items = scene->items();
    for (auto &x : items) {
        x->setGraphicsEffect(nullptr);
        if (typeid(*x) == typeid(QGraphicsTextItem)) {
            scene->removeItem(x);
        }
    }
    return false;
}

void change_position(int step_size, sprite *walker, directions dir) {
    auto x = walker->x();
    auto y = walker->y();
    switch (dir) {
        case directions::UP:
            walker->setPos(x, y - step_size);
            break;
        case directions::DOWN:
            walker->setPos(x, y + step_size);
            break;
        case directions::RIGHT:
            walker->setPos(x + step_size, y);
            break;
        case directions::LEFT:
            walker->setPos(x - step_size, y);
            break;
    }
    walker->is_colliding();
    walker->name_display->setPos(walker->name_display->x() + walker->x() - x,
                                 walker->name_display->y() + walker->y() - y);
    x = walker->x();
    y = walker->y();
    user moved(walker->name, "placeholder", "skin", x, y);
    emit walker->run_send_request(
        moved.serialize(ChitChatMessage::Query_RequestType_MOVE));
    qDebug() << std::to_string(walker->x()).c_str()
             << std::to_string(walker->y()).c_str();
}

sprite_for_choice::sprite_for_choice(const std::string &skin) : skin(skin) {
    setPixmap(QPixmap(":/images/" + QString(skin.c_str()) + "_sprite.png"));
}

void sprite_for_choice::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit run_send_skin(skin);
    emit this->add_curren_sprite();
}

sprite_of_object::sprite_of_object(const std::string &object)
    : QGraphicsPixmapItem(
          QPixmap(":/images/" + QString(object.c_str()) + ".png")) {
    type_of_object = object;
}

void sprite_of_object::set_text(const std::string &message) {
    text = new QGraphicsTextItem(message.c_str());
}
