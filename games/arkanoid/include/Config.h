#ifndef ARKANOID_CONFIG_H
#define ARKANOID_CONFIG_H

#include <QApplication>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include "boost/config.hpp"

/// header-file that contains global constants and qt-includes needed for other entities

struct Config {
    constexpr static int MOVEMENT_FREQUENCY = 33;
    constexpr static int AMOUNT_OF_BRICKS_IN_ROW = 15;
    constexpr static double FIELD_WIDTH = 500;
    constexpr static double FIELD_HEIGHT = 500;
    constexpr static double SPACE_BETWEEN_BRICKS = 2;
    constexpr static double SPEED_VECTOR_LENGTH = 4;
    constexpr static double PADDING = (AMOUNT_OF_BRICKS_IN_ROW + 1) * SPACE_BETWEEN_BRICKS;
    constexpr static double BRICK_WIDTH = (FIELD_WIDTH - PADDING) / static_cast<double>(AMOUNT_OF_BRICKS_IN_ROW);
    constexpr static double BRICK_HEIGHT = BRICK_WIDTH * 0.6;
};


#endif//ARKANOID_CONFIG_H
