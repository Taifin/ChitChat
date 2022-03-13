#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsRectItem>

class sprite : public QGraphicsRectItem
{
public:

    void keyPressEvent(QKeyEvent *event);
};

#endif // SPRITE_H
