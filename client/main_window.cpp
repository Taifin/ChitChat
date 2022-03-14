#include "main_window.h"
#include "./ui_main_window.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QApplication>
#include "sprite.h"
#include <map>
#include "user.h"

extern client_socket socket;
extern network::client server;
extern user current_user;


main_window::main_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::main_window)
{
    connect(&login_m, SIGNAL(show_main_window()), this, SLOT(show_after_auth()));

    connect(&socket, SIGNAL(run_already_connected()), this, SLOT(already_connected()));
    connect(&socket, SIGNAL(run_connect_with_room()), this, SLOT(connect_with_room()));

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
    socket.send_datagram("connect," + current_user.name() +","+ current_user.pwd(), server);
}

void main_window::already_connected()
{
    ui->statusbar->showMessage("Wait dude, you're already in the room");
}

void main_window::connect_with_room()
{
    QGraphicsScene *scene = new QGraphicsScene();
    sprite *sprite_current_user = new sprite();
    sprite_current_user->setRect(0,0,30,30);



 /*   //играюсь:Р

    std::map<std::string, sprite*> aboba;
    sprite *kek = new sprite();
    kek->setRect(30,30,30,30);
    aboba["kek"] = kek;


    for (auto &x : aboba){
        scene->addItem(x.second);
    }

*/
    scene->addItem(sprite_current_user);
    sprite_current_user->setFlag(QGraphicsItem::ItemIsFocusable);
    sprite_current_user->setFocus();

    QGraphicsView *view = ui->room_view;
    view->setScene(scene);


}



