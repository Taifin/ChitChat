#include "main_window.h"
#include <QApplication>

#include <QMetaType>
#include <chrono>
#include <map>
#include <memory>
#include <thread>
#include "./ui_main_window.h"
#include "client_user.h"
#include "sprite.h"

extern QTcpSocket *remote_server;

extern client_user current_user;
extern std::map<std::string, client_user> users_in_the_room;
extern client_processor processor;

main_window::main_window(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::main_window) {
    scene = new QGraphicsScene();

    remote_server->connectToHost(QHostAddress("194.169.163.120"), 1235);

    qRegisterMetaType<std::vector<std::string>>("std::vector<std::string>");
    connect(&login_m, SIGNAL(show_main_window()), this,
            SLOT(show_after_auth()));

    connect(&processor, SIGNAL(run_already_connected()), this,
            SLOT(already_connected()));
    connect(&processor, SIGNAL(run_connect_with_room(std::vector<std::string>)),
            this, SLOT(connect_with_room(std::vector<std::string>)));
    connect(&processor, SIGNAL(run_change_position(std::string,int,int)),
            this, SLOT(change_position(std::string,int,int)));
    connect(&processor, SIGNAL(run_disconnect_roommate(const std::string &)),
            this, SLOT(roommate_disconnect(const std::string &)));
    connect(&processor, SIGNAL(run_connect_roommate(const std::string &)), this,
            SLOT(roommate_connect(const std::string &)));


    ui->setupUi(this);
    this->setWindowTitle("ChitChat");
    view = ui->room_view;
    view->setFixedSize(600, 550);
    qDebug() << view->y() <<" "<< view->x() << " " << view->width() << " " << view->height();
    scene->setSceneRect(scene->itemsBoundingRect());

    view->x(),
    view->setScene(scene);
    scene->setBackgroundBrush(QBrush(QImage(":/images/background.png")));
}

void main_window::start() {
    login_m.show();
}

void main_window::show_after_auth() {
    this->show();
};

main_window::~main_window() {
    delete scene;

    processor.prepare_query("disconnect," + current_user.name() + "," +
                                current_user.pwd() + "," +
                                std::to_string(current_user.get_x()) + "," +
                                std::to_string(current_user.get_y()),

                            remote_server);
}

void main_window::on_connect_button_clicked() {
    processor.prepare_query(
        "connect," + current_user.name() + "," + current_user.pwd(),
        remote_server);
    ui->change_avatar_button->hide();
}

void main_window::already_connected() {
    ui->statusbar->showMessage("Wait dude, you're already in the room");
}

void main_window::connect_with_room(std::vector<std::string> data) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    current_user.set_user_sprite();

    scene->setBackgroundBrush(QBrush(QImage(":/images/floor.png")));

    for (int i = 1; i < data.size(); i += 3) {
        if (data[i] != current_user.name()) {
            client_user u(data[i], "psw", stoi(data[i + 1]), stoi(data[i + 2]));
            users_in_the_room[data[i]] = u;
            users_in_the_room[data[i]].set_user_sprite();
            users_in_the_room[data[i]].user_sprite->setPos(stoi(data[i + 1]), stoi(data[i + 2]));
            users_in_the_room[data[i]].user_sprite->name_display->setPlainText(
                QString(users_in_the_room[data[i]].name().c_str()));
            users_in_the_room[data[i]].user_sprite->name_display->setPos(
                stoi(data[i + 1]), stoi(data[i + 2]) - 20);
            scene->addItem(users_in_the_room[data[i]].user_sprite);
            scene->addItem(
                users_in_the_room[data[i]].user_sprite->name_display);
        }
    }

    current_user.user_sprite->name_display->setPlainText(
        QString(current_user.name().c_str()));
    current_user.user_sprite->name_display->setPos(0, -20);

    scene->addItem(current_user.user_sprite);
    scene->addItem(current_user.user_sprite->name_display);
    current_user.user_sprite->setFlag(QGraphicsItem::ItemIsFocusable);
    current_user.user_sprite->setFocus();    
}

void main_window::change_position(std::string name, int x, int y) {
    users_in_the_room[name].user_sprite->setPos(x, y);
    users_in_the_room[name].user_sprite->name_display->setPos(x, y -20);
}

void main_window::roommate_disconnect(const std::string &roommate_name) {
    scene->removeItem(users_in_the_room[roommate_name].user_sprite->name_display);
    scene->removeItem(users_in_the_room[roommate_name].user_sprite);
    users_in_the_room.erase(roommate_name);
}

void main_window::roommate_connect(const std::string &roommate_name) {
    client_user u(roommate_name, "pwd", 0, 0);
    users_in_the_room[roommate_name] = u;
    users_in_the_room[roommate_name].set_user_sprite();
    users_in_the_room[roommate_name].user_sprite->name_display->setPlainText(QString(roommate_name.c_str()));
    users_in_the_room[roommate_name].user_sprite->name_display->setPos(0, -20);
    scene->addItem(users_in_the_room[roommate_name].user_sprite);
    scene->addItem(users_in_the_room[roommate_name].user_sprite->name_display);
}

void main_window::on_change_avatar_button_clicked()
{

    //view->setEnabled(true);
    std::vector<std::string> characters = {"finn", "gambol", "miku", "mushroom", "rafael", "sonic", "stormtroopers", "kermit", "pikachu"};
    for (int i = 0; i < 9; i++){
        sprite_for_choice *skin = new sprite_for_choice(characters[i]);
        connect(skin, SIGNAL(clean_scene_after_choice()), scene, SLOT(clear()));
        scene->addItem(skin);
        skin->setPos(150+((i % 3)*100), 120+((i / 3)*100));
    }
}

