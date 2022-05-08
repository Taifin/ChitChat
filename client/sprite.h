#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QObject>
#include <unordered_map>
#include <QtGui>

enum class directions { UP, DOWN, LEFT, RIGHT };

class sprite : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    sprite(const std::string &name, std::string skin);
    void keyPressEvent(QKeyEvent *event);

    const std::string &name;

    ~sprite();

    QGraphicsTextItem *name_display = new QGraphicsTextItem;

    void change_skin(const std::string &skin);
};

void change_position(int step_size, sprite *walker, directions dir);

class sprite_for_choice : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    sprite_for_choice(const std::string &skin);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    std::string skin;
signals:
    void add_curren_sprite();
};

#endif  // SPRITE_H
