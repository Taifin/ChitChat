#include "include/Ball.h"

void Ball::move() {
    qDebug() << pos();
    for (int i = 1; i < this->collidingItems().size(); i++) {
        if (this->collidingItems()[i] != plank &&
            this->collidingItems()[i]->isVisible()) {
            brick_bounce(this->collidingItems()[i]);
            emit(brick_collision(this->collidingItems()[i]));
        } else if (this->collidingItems()[i] == plank) {
            plank_bounce();
        }
    }
    wall_bounce(Config::FIELD_WIDTH / 2, Config::FIELD_HEIGHT / 2);
    this->setPos(x() + speed * velocity.x, y() + speed * velocity.y);
}

void Ball::wall_bounce(qreal x_, qreal y_) {
    if (this->left() < -x_)
        velocity.x = absolute_velocity.x;
    if (this->right() > x_)
        velocity.x = -absolute_velocity.x;
    if (this->top() < -y_)
        velocity.y = absolute_velocity.y;
    //    if (this->bottom() > y_) velocity.y = -absolute_velocity.y;
    if (this->bottom() > y_)
        emit(ball_destroyed());
}
void Ball::brick_bounce(QGraphicsItem *brick) {
    auto right_overlap = right() + 250 - brick->boundingRect().left();
    auto left_overlap = left() + 250 - brick->boundingRect().right();
    auto top_overlap = bottom() + 250 - brick->boundingRect().top();
    auto bottom_overlap = top() + 250 - brick->boundingRect().bottom();
    bool x_direction = left_overlap < right_overlap;
    bool y_direction = top_overlap < bottom_overlap;
    auto x_delta = (x_direction) ? left_overlap : right_overlap;
    auto y_delta = (y_direction) ? top_overlap : bottom_overlap;
    if (abs(x_delta) > abs(y_delta)) {
        velocity.y = (y_direction) ? -absolute_velocity.y : absolute_velocity.y;
    } else {
        velocity.x = (x_direction) ? -absolute_velocity.x : absolute_velocity.x;
    }
}

void Ball::plank_bounce() {
    velocity.y = -absolute_velocity.y;
    if (bottom() >
        plank->y() + Config::FIELD_HEIGHT / 2 - plank->boundingRect().y()) {
        if (left() < plank->x()) {
            velocity.x = -absolute_velocity.x;
        } else {
            velocity.x = absolute_velocity.x;
        }
    }
}

qreal Ball::left() {
    return x();
}
qreal Ball::right() {
    return x() + this->rect().width();
}
qreal Ball::top() {
    return y();
}
qreal Ball::bottom() {
    return y() + this->rect().height();
}
Ball::Ball(QGraphicsItem *plank_) { // NOLINT : randomize_velocity do the thing
    plank = plank_;
    randomize_velocity();
}

void Ball::randomize_velocity() {
    velocity = {static_cast<float>(gen_int(rng)),
                static_cast<float>(gen_int(rng))};
    absolute_velocity = {abs(velocity.x), abs(velocity.y)};
    speed = Config::SPEED_VECTOR_LENGTH /
            std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
}
