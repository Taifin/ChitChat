#include "main_window.h"
#include "./ui_main_window.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QApplication>
#include "sprite.h"
#include <map>
#include "client_user.h"
#include <memory>
#include <chrono>
#include <thread>

extern client_socket socket;
extern network::client server;
extern client_user current_user;
extern std::map<std::string, client_user> users_in_the_room;


main_window::main_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::main_window)
{
    scene = new QGraphicsScene();
    //sprite_current_user = new sprite();

    connect(&login_m, SIGNAL(show_main_window()), this, SLOT(show_after_auth()));

    connect(&socket, SIGNAL(run_already_connected()), this, SLOT(already_connected()));
    connect(&socket, SIGNAL(run_connect_with_room(std::vector<std::string>)), this, SLOT(connect_with_room(std::vector<std::string>)));

    //connect(&socket, SIGNAL(run_initialize_users_in_the_room(std::vector<std::string>)), this, SLOT(initialize_users_in_the_room(std::vector<std::string>)));

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
    delete scene;
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

void main_window::connect_with_room(std::vector<std::string> data)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
/*
    for (int i = 1; i < data.size(); i += 3){
        client_user u(data[i+1], data[i+2]);
        users_in_the_room.emplace(data[i], u);
    }*/

    current_user.user_sprite->setRect(0,0,30,30);
    current_user.user_sprite->name_display->setPlainText(QString(current_user.name().c_str()));
    current_user.user_sprite->name_display->setPos(0, -20);
/*
    for (auto &x : users_in_the_room){
        qDebug() << x.first.c_str();
        scene->addItem(x.second.user_sprite);
        //scene->addItem(x.second.user_sprite->name_display);
    }

    //scene->addItem(users_in_the_room["1234"].user_sprite);

    for (auto &x : users_in_the_room){
        scene->addItem(x.second.user_sprite);
        //scene->addItem(x.second.user_sprite->name_display);
    }
    */

    scene->addItem(current_user.user_sprite);
    scene->addItem(current_user.user_sprite->name_display);
    current_user.user_sprite->setFlag(QGraphicsItem::ItemIsFocusable);
    current_user.user_sprite->setFocus();

    QGraphicsView *view = ui->room_view;
    view->setScene(scene);

}




