#include "main_window.h"
#include <QApplication>
#include <QMetaType>
#include <chrono>
#include <map>
#include <memory>
#include <thread>
#include "./ui_main_window.h"
#include "client_user.h"
#include "room.h"
#include "sprite.h"


main_window::main_window(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::main_window), font("Source Code Pro", 28, QFont::Bold) {
    scene = new room();
    ui->setupUi(this);
    this->setWindowTitle("ChitChat");
    view = ui->room_view;
    view->setFixedSize(600, 550);
    qDebug() << view->y() << " " << view->x() << " " << view->width() << " "
             << view->height();
    scene->setSceneRect(scene->itemsBoundingRect());

    view->x(), view->setScene(scene);
    scene->setBackgroundBrush(QBrush(QImage(":/images/background.png")));

    timer =  new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(remove_message()));

}

void main_window::show_after_auth() {
    this->show();
    show_curren_sprite();
};

main_window::~main_window() {
    delete scene;
    emit run_send_request("disconnect," + current_user.name() + "," +
                          current_user.pwd() + "," +
                          std::to_string(current_user.get_x()) + "," +
                          std::to_string(current_user.get_y()));

}

void main_window::remove_message()
{
    ui->statusbar->clearMessage();
}

void main_window::on_connect_button_clicked() {
    run_send_request("connect," + current_user.name() + "," +
                     current_user.pwd());
    ui->change_avatar_button->hide();
}

void main_window::already_connected() {
    ui->statusbar->showMessage("Wait dude, you're already in the room");
    timer->start(TIME_FOR_MESSAGE);
}

void main_window::set_sprite_name(sprite *sprite){
    QFontMetrics fm(font);
    int wide = fm.width(sprite->name_display->text());
    qDebug() << (wide) << sprite->x();
    sprite->name_display->setPos(sprite->x()+36 - (wide/5), sprite->y()-20);
}

void main_window::connect_with_room(std::vector<std::string> data) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    scene->clear();
    scene->addItem(scene->game_machine);
    scene->game_machine->setPos(100, 70);
    set_user_sprite();

    scene->set_curren_user_sprite(current_user.user_sprite);

    scene->setBackgroundBrush(QBrush(QImage(":/images/floor.png")));

    for (int i = 1; i < data.size(); i += 3) {
        if (data[i] != current_user.name()) {
            client_user u(data[i], "psw", stoi(data[i + 1]), stoi(data[i + 2]));
            users_in_the_room[data[i]] = u;
            users_in_the_room[data[i]].set_user_sprite();
            users_in_the_room[data[i]].user_sprite->setPos(stoi(data[i + 1]),
                                                           stoi(data[i + 2]));
            users_in_the_room[data[i]].user_sprite->name_display->setText(
                QString(users_in_the_room[data[i]].name().c_str()));
            set_sprite_name(users_in_the_room[data[i]].user_sprite);
            //users_in_the_room[data[i]].user_sprite->name_display->setPos(
                //stoi(data[i + 1]), stoi(data[i + 2]) - 20);
            scene->addItem(users_in_the_room[data[i]].user_sprite);
            scene->addItem(
                users_in_the_room[data[i]].user_sprite->name_display);
        }
    }

    current_user.user_sprite->name_display->setText(
        QString(current_user.name().c_str()));
    set_sprite_name(current_user.user_sprite);
    //current_user.user_sprite->name_display->setPos(0, -20);

    scene->addItem(current_user.user_sprite);
    scene->addItem(current_user.user_sprite->name_display);

    current_user.user_sprite->setFlag(QGraphicsItem::ItemIsFocusable);

    // current_user.user_sprite->setFocusPolicy(QT::StrongFocus);
    current_user.user_sprite->setFocus();
}

void main_window::user_changed_position(std::string name, int x, int y) {
    users_in_the_room[name].user_sprite->setPos(x, y);
    users_in_the_room[name].user_sprite->name_display->setPos(x, y - 20);
}

void main_window::roommate_disconnect(const std::string &roommate_name) {
    scene->removeItem(
        users_in_the_room[roommate_name].user_sprite->name_display);
    scene->removeItem(users_in_the_room[roommate_name].user_sprite);
    users_in_the_room.erase(roommate_name);
}



void main_window::roommate_connect(const std::string &roommate_name) {
    client_user u(roommate_name, "pwd", 0, 0);
    users_in_the_room[roommate_name] = u;
    users_in_the_room[roommate_name].set_user_sprite();
    users_in_the_room[roommate_name].user_sprite->name_display->setText(
        QString(roommate_name.c_str()));
    set_sprite_name(users_in_the_room[roommate_name].user_sprite);
    //users_in_the_room[roommate_name].user_sprite->name_display->setPos(0, -20);
    scene->addItem(users_in_the_room[roommate_name].user_sprite);
    scene->addItem(users_in_the_room[roommate_name].user_sprite->name_display);
}

void main_window::show_curren_sprite() {
    scene->clear();

    QGraphicsSimpleTextItem *text = new QGraphicsSimpleTextItem("Your character");
    QPen pen;

    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);
    pen.setBrush(Qt::black);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setColor(Qt::white);
    text->setPen(pen);


    text->setFont(font);
    scene->addItem(text);

    text->setPos(140, 160);

    QGraphicsPixmapItem *user_skin = new QGraphicsPixmapItem(
        QPixmap(":/images/" + QString(current_user.get_skin().c_str()) +
                "_sprite.png"));
    scene->addItem(user_skin);
    user_skin->setPos(250, 220);
}

void main_window::set_user_skin(const std::string &skin) {
    current_user.skin = skin;
}

void main_window::on_change_avatar_button_clicked() {
    // view->setEnabled(true);
    scene->clear();

    QPen pen;

    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);
    pen.setBrush(Qt::black);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setColor(Qt::white);

    QGraphicsSimpleTextItem *text =
        new QGraphicsSimpleTextItem("Select a character by clicking on it");
    QFont font("Source Code Pro", 18, QFont::Bold);
    text->setFont(font);
    scene->addItem(text);
    text->setPos(70, 80);
    text->setPen(pen);

    std::vector<std::string> characters = {
        "finn",  "gambol",        "miku",   "mushroom", "rafael",
        "sonic", "stormtroopers", "kermit", "pikachu"};
    for (int i = 0; i < 9; i++) {
        sprite_for_choice *skin = new sprite_for_choice(characters[i]);
        connect(skin, SIGNAL(add_curren_sprite()), this,
                SLOT(show_curren_sprite()));
        scene->addItem(skin);

        skin->setPos(150 + ((i % 3) * 100), 120 + ((i / 3) * 100));
    }
}

void main_window::set_user_sprite() {
    current_user.user_sprite =
        new sprite(current_user.name(), current_user.get_skin());
    connect(current_user.user_sprite,
            SIGNAL(run_send_request(const std::string &)), current_session,
            SLOT(send_request(const std::string &)));
}



