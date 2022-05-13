#ifndef ARKANOID_BALL_H
#define ARKANOID_BALL_H

#include <random>
#include "Config.h"

static std::mt19937 rng(
    std::chrono::steady_clock::now().time_since_epoch().count());
static std::uniform_real_distribution<> gen_int(-1, 1);

struct vector {
    float x;
    float y;
};

struct Game;

class Ball : public QObject, public QGraphicsRectItem {
    Q_OBJECT

    friend Game;

public:
    Ball(QGraphicsItem *plank);

public slots:
    void move();

signals:
    void brick_collision(QGraphicsItem *);

    void ball_destroyed();

private:
    vector velocity;
    vector absolute_velocity;
    double speed;
    QGraphicsItem *plank;

    void wall_bounce(qreal x_, qreal y_);

    void brick_bounce(QGraphicsItem *brick);

    void plank_bounce();

    void randomize_velocity();

    qreal left();

    qreal right();

    qreal top();

    qreal bottom();
};

#endif  // ARKANOID_BALL_H
