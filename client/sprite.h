#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsRectItem>

enum class directions {UP, DOWN, LEFT, RIGHT};
class sprite : public QGraphicsRectItem
{
public:
    void keyPressEvent(QKeyEvent *event);
};

void change_position(int step_size, sprite *walker, directions dir);

#endif // SPRITE_H
