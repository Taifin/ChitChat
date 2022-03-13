#include "main_window.h"
#include "./ui_main_window.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QApplication>
#include "sprite.h"

main_window::main_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::main_window)
{
    connect(&login_m, SIGNAL(show_main_window()), this, SLOT(show_after_auth()));
    ui->setupUi(this);
    this->setWindowTitle("ChitChat");
}

void main_window::start(){
    login_m.show();
}

void main_window::show_after_auth(){
    this->show();
};

main_window::~main_window()
{
    delete ui;
}


void main_window::on_connect_button_clicked()
{
    QGraphicsScene *scene = new QGraphicsScene();
    sprite *sprite_current_user = new sprite();
    sprite_current_user->setRect(0,0,30,30);

    scene->addItem(sprite_current_user);
    sprite_current_user->setFlag(QGraphicsItem::ItemIsFocusable);
    sprite_current_user->setFocus();

    QGraphicsView *view = ui->room_view;
    view->setScene(scene);
}

