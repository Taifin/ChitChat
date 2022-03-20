#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsRectItem>
#include <QObject>

enum class directions {UP, DOWN, LEFT, RIGHT};

class sprite : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    sprite(std::string name);
    void keyPressEvent(QKeyEvent *event);

    std::string name;

    ~sprite();

    QGraphicsTextItem *name_display = new QGraphicsTextItem;
};

void change_position(int step_size, sprite *walker, directions dir);

#endif // SPRITE_H
