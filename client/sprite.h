#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsRectItem>
#include <QObject>

enum class directions {UP, DOWN, LEFT, RIGHT};

class sprite : public QGraphicsRectItem
{

public:
    sprite();
    void keyPressEvent(QKeyEvent *event);

    ~sprite();

    QGraphicsTextItem *name_display = new QGraphicsTextItem;
};

void change_position(int step_size, sprite *walker, directions dir);

#endif // SPRITE_H
