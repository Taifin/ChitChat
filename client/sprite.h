#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QObject>
#include <QtGui>
#include <unordered_map>
#include "message.pb.h"

static int STEP_SIZE = 5;

enum class directions { UP, DOWN, LEFT, RIGHT };

class sprite : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    sprite(const std::string &name, const std::string &skin);
    void keyPressEvent(QKeyEvent *event) override;

    const std::string &name;

    ~sprite() override;

    QGraphicsSimpleTextItem *name_display = new QGraphicsSimpleTextItem;

    void change_skin(const std::string &skin);

    bool is_colliding();

signals:
    void run_send_request(const ChitChatMessage::Query &message);
};

void change_position(int step_size, sprite *walker, directions dir);

class sprite_for_choice : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    explicit sprite_for_choice(const std::string &skin);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    std::string skin;

signals:
    void add_curren_sprite();
    void run_send_skin(const std::string &message);
};

class sprite_of_object : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    explicit sprite_of_object(const std::string &object);
    std::string type_of_object;
    QGraphicsTextItem *text;

    void set_text(const std::string &message) {
        text = new QGraphicsTextItem(message.c_str());
    }
};

#endif  // SPRITE_H
