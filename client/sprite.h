#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsRectItem>
#include <QObject>

enum class directions {UP, DOWN, LEFT, RIGHT};

class sprite : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    sprite();
    void keyPressEvent(QKeyEvent *event);

    ~sprite();

    QGraphicsTextItem *name_display = new QGraphicsTextItem;
};

void change_position(int step_size, sprite *walker, directions dir);

#endif // SPRITE_H
