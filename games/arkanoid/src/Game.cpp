#include "include/Game.h"

// TODO: stop game after window is closed

Game::Game() {
    prepare_menu_scene();
    prepare_game_scene();
    prepare_end_scene();
    game_view->setScene(start_scene);
    game_view->setFixedSize(Config::FIELD_WIDTH + 50,
                            Config::FIELD_HEIGHT + 50);
}

Game::~Game() {
    delete p;
    delete b;
    delete movement_timer;
    delete score_widget;
    delete lives_widget;
}

void Game::destroy_brick(QGraphicsItem *brick) {
    brick->setVisible(false);
    score_widget->setNum(int(score += 10));
    score_widget->adjustSize();
    if (score == Config::AMOUNT_OF_BRICKS_IN_ROW * 10 * 5) {
        end_game();
    }
}

void Game::start_game() {
    new_ball();
    for (auto item : game_scene->items()) {
        item->setVisible(true);
    }
    score = 0;
    lives = 0;
    score_widget->setNum(0);
    score_widget->adjustSize();
    game_view->setScene(game_scene);
    movement_timer->start(Config::MOVEMENT_FREQUENCY);
}

void Game::new_ball() {
    b->setPos(0, 0);
    b->randomize_velocity();
}

void Game::fail() {
    if (--lives != 0) {
        lives_widget->setNum(int(lives));
        new_ball();
    } else {
        end_game();
    }
}

void Game::end_game() {
    movement_timer->stop();
    score += 100 * lives;
    game_over_score_widget->setNum(int(score));
    game_over_score_widget->adjustSize();
    game_view->setScene(end_scene);
}

void Game::prepare_game_scene() {
    p->setRect(Config::FIELD_WIDTH / 2, Config::FIELD_HEIGHT - 50, 20, 10);
    b->setRect(Config::FIELD_WIDTH / 2, Config::FIELD_HEIGHT / 2, 20, 20);
    for (int i = 0; i < Config::AMOUNT_OF_BRICKS_IN_ROW; i++) {
        for (int j = 0; j < 5; j++) {
            game_scene->addItem(new QGraphicsRectItem(
                ((Config::FIELD_WIDTH - Config::PADDING) /
                 Config::AMOUNT_OF_BRICKS_IN_ROW) *
                        i +
                    Config::SPACE_BETWEEN_BRICKS * (i + 1),
                Config::FIELD_WIDTH / Config::AMOUNT_OF_BRICKS_IN_ROW * 0.8 * j,
                Config::BRICK_WIDTH, Config::BRICK_HEIGHT));
        }
    }
    auto *lives_text = new QGraphicsTextItem("lives:");
    auto *score_text = new QGraphicsTextItem("score:");
    lives_text->setPos(450, -24);
    score_text->setPos(0, -24);
    score_widget->move(45, -20);
    lives_widget->move(490, -20);
    game_scene->addItem(p);
    game_scene->addItem(b);
    game_scene->addItem(lives_text);
    game_scene->addItem(score_text);
    game_scene->addWidget(score_widget);
    game_scene->addWidget(lives_widget);
    game_scene->addItem(border);
    game_scene->setSceneRect(0, 0, Config::FIELD_WIDTH, Config::FIELD_HEIGHT);
    p->setFlag(QGraphicsItem::ItemIsFocusable);
    p->setFocus();
    QObject::connect(movement_timer, SIGNAL(timeout()), b, SLOT(move()));
    QObject::connect(b, SIGNAL(brick_collision(QGraphicsItem *)), this,
                     SLOT(destroy_brick(QGraphicsItem *)));
    QObject::connect(b, SIGNAL(ball_destroyed()), this, SLOT(fail()));
}

void Game::prepare_menu_scene() {
    start_button->setText("Start new game");
    start_scene->addWidget(start_button);
    connect(start_button, SIGNAL(pressed()), this, SLOT(start_game()));
}

void Game::prepare_end_scene() {
    game_over_score_widget->move(100, 80);
    game_over_text->setTextWidth(200);
    game_over_text->setPos(50, 50);
    auto *restart_button = new QPushButton("Restart");
    auto *menu_button = new QPushButton("Menu");
    restart_button->move(60, 200);
    menu_button->move(150, 200);
    connect(restart_button, SIGNAL(pressed()), this, SLOT(start_game()));
    connect(menu_button, SIGNAL(pressed()), this, SLOT(show_menu()));
    end_scene->addItem(game_over_text);
    end_scene->addWidget(restart_button);
    end_scene->addWidget(menu_button);
    end_scene->addWidget(game_over_score_widget);
}

void Game::show_menu() {
    game_view->setScene(start_scene);
}

void Game::start() {
    game_view->show();
    game_view->activateWindow();
}

extern "C" Q_DECL_EXPORT ChitChat_game *get_game() {
    return reinterpret_cast<ChitChat_game *>(new Game());
}
