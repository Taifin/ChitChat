#ifndef ARKANOID_PLATFORM_H
#define ARKANOID_PLATFORM_H

#include "Config.h"

class Plank : public QGraphicsRectItem {

public:
    void keyPressEvent(QKeyEvent *event) override;

    void change_pos(int step, int direction);
};
#endif//ARKANOID_PLATFORM_H
