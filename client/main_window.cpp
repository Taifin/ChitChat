#include "main_window.h"
#include <QMetaType>
#include <chrono>
#include <map>
#include <thread>
#include "./ui_main_window.h"
#include "client_user.h"
#include "room.h"
#include "sprite.h"

#define WIDTH 600
#define HEIGHT 550
#define NAME_INDENT 20

main_window::main_window(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::main_window),
      font("Source Code Pro", 13, QFont::Bold) {
    scene = new room();
    ui->setupUi(this);
    this->setWindowTitle("ChitChat");
    ui->microphone_check->hide();
    ui->headphones_check->hide();
    move(QGuiApplication::screens().at(0)->geometry().center() -
         frameGeometry().center());
    view = ui->room_view;
    view->setFixedSize(WIDTH, HEIGHT);
    qDebug() << view->y() << " " << view->x() << " " << view->width() << " "
             << view->height();
    scene->setSceneRect(scene->itemsBoundingRect());

    view->x(), view->setScene(scene);
    scene->setBackgroundBrush(QBrush(QImage(":/images/background.png")));

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(remove_message()));

    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);
    pen.setBrush(QColor(117, 5, 48));
    brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);

    ui->statusbar->setStyleSheet("background-color: rgb(169, 231, 245);");
    this->lower();
}

void main_window::show_after_auth() {
    this->show();
    show_current_sprite();
    this->activateWindow();
}

main_window::~main_window() {
    delete scene;
    emit run_send_request(
        current_user.serialize(ChitChatMessage::Query_RequestType_DISCONNECT));
}

void main_window::remove_message() {
    ui->statusbar->clearMessage();
}

void main_window::on_connect_button_clicked() {
    if (ui->connect_button->text() == "connect") {
        run_send_request(
            current_user.serialize(ChitChatMessage::Query_RequestType_CONNECT));
        btn = new QPushButton("Terminate");
        ui->verticalLayout_2->addWidget(btn);
        connect(btn, SIGNAL(pressed()), this, SLOT(terminate()));
        ui->change_avatar_button->hide();
        ui->connect_button->setText("disconnect");
        ui->microphone_check->show();
        ui->headphones_check->show();
    } else if (ui->connect_button->text() == "disconnect") {
        run_send_request(current_user.serialize(
            ChitChatMessage::Query_RequestType_DISCONNECT));
        ui->microphone_check->hide();
        ui->headphones_check->hide();
        ui->microphone_check->setChecked(false);
        ui->headphones_check->setChecked(false);
        ui->connect_button->setText("connect");
        scene->clear();
        scene->setBackgroundBrush(QBrush(QImage(":/images/background.png")));
        ui->change_avatar_button->show();
        show_current_sprite();
    }
}

void main_window::already_connected() {
    ui->statusbar->showMessage("Wait dude, you're already in the room");
    timer->start(TIME_FOR_MESSAGE);
}

void main_window::set_sprite_name(sprite *sprite) {
    QFontMetrics fm(font);
    int wide = fm.width(sprite->name_display->text());
    qDebug() << (wide) << sprite->x();
    sprite->name_display->setPos(sprite->x() + 36 - (wide / 2),
                                 sprite->y() - NAME_INDENT);
    sprite->name_display->setPen(pen);
    sprite->name_display->setBrush(brush);
    sprite->name_display->setFont(font);
}

void main_window::connect_with_room(const ChitChatMessage::Query &data) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    scene->clear();
    scene->set_game_machine();
    scene->addItem(scene->game_machine);
    scene->game_machine->setPos(100, 70);
    set_user_sprite();

    scene->set_curren_user_sprite(current_user.user_sprite);

    scene->setBackgroundBrush(QBrush(QImage(":/images/floor.png")));

    for (const auto &user : data.users()) {
        if (user.name() != current_user.get_name()) {
            client_user u;
            u.parse(user);
            initialize_user(u);
            users_in_the_room.insert({u.get_name(), u});
            scene->addItem(u.user_sprite);
            scene->addItem(u.user_sprite->name_display);
        }
    }

    current_user.user_sprite->name_display->setText(
        QString(current_user.get_name().c_str()));
    current_user.user_sprite->name_display->setPos(0, -NAME_INDENT);
    set_sprite_name(current_user.user_sprite);

    scene->addItem(current_user.user_sprite);
    scene->addItem(current_user.user_sprite->name_display);

    current_user.user_sprite->setFlag(QGraphicsItem::ItemIsFocusable);
    current_user.user_sprite->setFocus();
}

void main_window::user_changed_position(const std::string &name, int x, int y) {
    users_in_the_room[name].user_sprite->setPos(x, y);
    set_sprite_name(users_in_the_room[name].user_sprite);
}

void main_window::roommate_disconnect(const std::string &roommate_name) {
    scene->removeItem(
        users_in_the_room[roommate_name].user_sprite->name_display);
    scene->removeItem(users_in_the_room[roommate_name].user_sprite);
    users_in_the_room.erase(roommate_name);
}

void main_window::roommate_connect(
    const ChitChatMessage::Query &roommate_data) {
    client_user u;
    u.parse_from(roommate_data);
    initialize_user(u);
    users_in_the_room.insert({u.get_name(), u});
    scene->addItem(u.user_sprite);
    scene->addItem(u.user_sprite->name_display);
}

void main_window::show_current_sprite() {
    scene->clear();
    auto *text = new QGraphicsSimpleTextItem("Your character");

    QFont sprite_font("Source Code Pro", 28, QFont::Bold);

    text->setFont(sprite_font);
    scene->addItem(text);

    text->setPos(140, 160);

    auto *user_skin = new QGraphicsPixmapItem(
        QPixmap(":/images/" + QString(current_user.get_skin().c_str()) +
                "_sprite.png"));

    scene->addItem(user_skin);
    user_skin->setPos(250, 220);
}

void main_window::send_skin(const std::string &skin) {
    current_user.change_skin(skin);
    run_send_request(
        current_user.serialize(ChitChatMessage::Query_RequestType_CHANGE_SKIN));
}

void main_window::set_user_skin(const std::string &skin) {
    current_user.set_skin(skin);
}

void main_window::on_change_avatar_button_clicked() {
    scene->clear();

    auto *text =
        new QGraphicsSimpleTextItem("Select a character by clicking on it");
    QFont avatar_font("Source Code Pro", 18, QFont::Bold);

    QPen avatar_pen;

    avatar_pen.setStyle(Qt::SolidLine);
    avatar_pen.setWidth(1);
    avatar_pen.setBrush(Qt::black);
    avatar_pen.setCapStyle(Qt::RoundCap);
    avatar_pen.setJoinStyle(Qt::RoundJoin);
    avatar_pen.setColor(Qt::white);
    text->setPen(avatar_pen);

    text->setFont(avatar_font);

    scene->addItem(text);
    text->setPos(70, 80);
    text->setPen(avatar_pen);

    std::vector<std::string> characters = {
        "finn",  "gambol",        "miku",   "mushroom", "rafael",
        "sonic", "stormtroopers", "kermit", "pikachu"};
    for (int i = 0; i < 9; i++) {
        auto *skin = new sprite_for_choice(characters[i]);
        connect(skin, SIGNAL(add_curren_sprite()), this,
                SLOT(show_current_sprite()));
        connect(skin, SIGNAL(run_send_skin(std::string)), this,
                SLOT(send_skin(std::string)));
        scene->addItem(skin);

        skin->setPos(150 + ((i % 3) * 100), 120 + ((i / 3) * 100));  // NOLINT
    }
}

void main_window::set_user_sprite() {
    current_user.user_sprite =
        new sprite(current_user.get_name(), current_user.get_skin());

    connect(current_user.user_sprite,
            SIGNAL(run_send_request(ChitChatMessage::Query)), current_session,
            SLOT(send_request(ChitChatMessage::Query)));
}

void main_window::on_headphones_check_stateChanged(int arg1) {
    if (!arg1) {  // if button is unpressed
        emit turn_head_off();
    } else {
        emit turn_head_on();
    }
}

void main_window::on_microphone_check_stateChanged(int arg1) {
    if (!arg1) {  // if button is unpressed
        emit turn_mic_off();
    } else {
        emit turn_mic_on();
    }
}
void main_window::initialize_user(client_user &u) {
    u.set_user_sprite();
    u.user_sprite->setPos(u.get_x(), u.get_y());
    u.user_sprite->name_display->setText(u.get_name().c_str());
    u.user_sprite->name_display->setPos(u.get_x(), u.get_y() - NAME_INDENT);
    set_sprite_name(u.user_sprite);
    u.user_sprite->change_skin(u.get_skin());
}
void main_window::terminate() {
    emit run_send_request(current_user.serialize(ChitChatMessage::Query_RequestType_DEBUG_TERMINATE));
}
