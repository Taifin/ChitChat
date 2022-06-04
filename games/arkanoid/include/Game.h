#ifndef GAME_H
#define GAME_H

#include <QScreen>
#include "Ball.h"
#include "Platform.h"
#include "abstract_game.h"

class Q_DECL_EXPORT Game : ChitChat_game {
    Q_OBJECT

public:
    Game();

    void prepare_game_scene();

    void prepare_menu_scene();

    void prepare_end_scene();

    void start() override;

    ~Game() override;

public slots:
    void destroy_brick(QGraphicsItem *brick);

    void fail();

    void start_game();

    void end_game();

    void show_menu();

private:
    Plank *p = new Plank();
    Ball *b = new Ball(p);
    QTimer *movement_timer = new QTimer();
    QLabel *score_widget = new QLabel("0");
    QLabel *lives_widget = new QLabel("3");
    QLabel *game_over_score_widget = new QLabel();
    QGraphicsScene *game_scene = new QGraphicsScene();
    QGraphicsScene *start_scene = new QGraphicsScene();
    QGraphicsScene *end_scene = new QGraphicsScene();
    QGraphicsView *game_view = new QGraphicsView();
    QGraphicsTextItem *game_over_text =
        new QGraphicsTextItem("Game is over! Your score is:");
    QPushButton *start_button = new QPushButton("Start new game");
    QGraphicsRectItem *border = new QGraphicsRectItem(0, 0, 500, 500);
    unsigned int lives = 3;
    unsigned int score = 0;
    void new_ball();
};
#endif  // GAME_H
