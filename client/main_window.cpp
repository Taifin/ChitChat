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
#include <QMetaType>

extern network::client server;
extern client_user current_user;
extern std::map<std::string, client_user> users_in_the_room;
extern client_processor processor;


main_window::main_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::main_window)
{
    scene = new QGraphicsScene();

    qRegisterMetaType<std::vector<std::string>>("std::vector<std::string>");
    connect(&login_m, SIGNAL(show_main_window()), this, SLOT(show_after_auth()));

    connect(&processor, SIGNAL(run_already_connected()), this, SLOT(already_connected()));
    connect(&processor, SIGNAL(run_connect_with_room(std::vector<std::string>)), this, SLOT(connect_with_room(std::vector<std::string>)));
    connect(&processor, SIGNAL(run_change_position(std::string,int,int)), this, SLOT(change_position(std::string,int,int)));
    ui->setupUi(this);
    this->setWindowTitle("ChitChat");
}

void main_window::start() {
    login_m.show();
}

void main_window::show_after_auth() {
    this->show();
};

main_window::~main_window() {
    delete scene;
    processor.prepare_query("disconnect," + current_user.name() +","+ current_user.pwd() +","+ std::to_string(current_user.get_x()) + "," + std::to_string(current_user.get_y()), server);
}

void main_window::on_connect_button_clicked()
{
    processor.prepare_query("connect," + current_user.name() +","+ current_user.pwd(), server);
}

void main_window::already_connected()
{
    ui->statusbar->showMessage("Wait dude, you're already in the room");
}

void main_window::connect_with_room(std::vector<std::string> data)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    scene->setSceneRect(-250, -250, 500, 500);

    for (int i = 1; i < data.size(); i += 3){
        if (data[i] != current_user.name()){
        client_user u(data[i], "psw", stoi(data[i+1]), stoi(data[i+2]));
        users_in_the_room[data[i]] = u;
        users_in_the_room[data[i]].user_sprite->setRect(stoi(data[i+1]),stoi(data[i+2]),30,30);
        users_in_the_room[data[i]].user_sprite->name_display->setPlainText(QString(users_in_the_room[data[i]].name().c_str()));
        users_in_the_room[data[i]].user_sprite->name_display->setPos(stoi(data[i+1]), stoi(data[i+2])-20);
        scene->addItem(users_in_the_room[data[i]].user_sprite);
        scene->addItem(users_in_the_room[data[i]].user_sprite->name_display);
        }
    }

    current_user.user_sprite->setRect(0,0,30,30);
    current_user.user_sprite->name_display->setPlainText(QString(current_user.name().c_str()));
    current_user.user_sprite->name_display->setPos(0, -20);

    scene->addItem(current_user.user_sprite);
    scene->addItem(current_user.user_sprite->name_display);
    current_user.user_sprite->setFlag(QGraphicsItem::ItemIsFocusable);
    current_user.user_sprite->setFocus();

    QGraphicsView *view = ui->room_view;
    view->setScene(scene);

}

void main_window::change_position(std::string name, int x, int y)
{
    users_in_the_room[name].user_sprite->setPos(x, y);
    users_in_the_room[name].user_sprite->name_display->setPos(x, y-20);
}



void main_window::roommate_disconnect(const std::string &roommate_name){
    scene->removeItem(users_in_the_room[roommate_name].user_sprite);
    scene->removeItem(users_in_the_room[roommate_name].user_sprite->name_display);
}
