#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QObject>
#include <unordered_map>

enum class directions { UP, DOWN, LEFT, RIGHT };

class sprite : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    sprite(const std::string &name, std::string skin = "kermit");
    void keyPressEvent(QKeyEvent *event);

    const std::string &name;

    ~sprite();

    QGraphicsTextItem *name_display = new QGraphicsTextItem;
};

void change_position(int step_size, sprite *walker, directions dir);

#endif  // SPRITE_H
