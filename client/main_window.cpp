#include "main_window.h"
#include <QMetaType>
#include <chrono>
#include <map>
#include <thread>
#include "./ui_main_window.h"
#include "client_user.h"
#include "room.h"
#include "sprite.h"

main_window::main_window(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::main_window) {
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
}

void main_window::show_after_auth() {
    this->show();
    show_curren_sprite();
}

main_window::~main_window() {
    delete scene;

    emit run_send_request("disconnect," + current_user.get_name() + "," +
                          current_user.get_password() + "," +
                          std::to_string(current_user.get_x()) + "," +
                          std::to_string(current_user.get_y()));
}

void main_window::on_connect_button_clicked() {
    run_send_request("connect," + current_user.get_name() + "," +
                     current_user.get_password());
    ui->change_avatar_button->hide();
}

void main_window::already_connected() {
    ui->statusbar->showMessage("Wait dude, you're already in the room");
}

void main_window::connect_with_room(const ChitChatMessage::Query &data) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    scene->clear();
    scene->addItem(scene->game_machine);
    scene->game_machine->setPos(100, 70);
    set_user_sprite();

    scene->set_curren_user_sprite(current_user.user_sprite);

    scene->setBackgroundBrush(QBrush(QImage(":/images/floor.png")));

    for (const auto& user : data.users()) {
        if (user.name() != current_user.get_name()) {
            client_user u;
            u.parse(user);
            initialize_user(u);
            users_in_the_room.insert({u.get_name(), u});
            scene->addItem(u.user_sprite);
            scene->addItem(u.user_sprite->name_display);
        }
    }

    current_user.user_sprite->name_display->setPlainText(
        QString(current_user.get_name().c_str()));
    current_user.user_sprite->name_display->setPos(0, -20);

    scene->addItem(current_user.user_sprite);
    scene->addItem(current_user.user_sprite->name_display);

    current_user.user_sprite->setFlag(QGraphicsItem::ItemIsFocusable);

    // current_user.user_sprite->setFocusPolicy(QT::StrongFocus);
    current_user.user_sprite->setFocus();
}

void main_window::user_changed_position(const std::string &name, int x, int y) {
    users_in_the_room[name].user_sprite->setPos(x, y);
    users_in_the_room[name].user_sprite->name_display->setPos(x, y - 20);
}

void main_window::roommate_disconnect(const std::string &roommate_name) {
    scene->removeItem(
        users_in_the_room[roommate_name].user_sprite->name_display);
    scene->removeItem(users_in_the_room[roommate_name].user_sprite);
    users_in_the_room.erase(roommate_name);
}

void main_window::roommate_connect(const ChitChatMessage::Query &roommate_data) {
    client_user u;
    u.parse(roommate_data);
    initialize_user(u);
    users_in_the_room.insert({u.get_name(), u});
    scene->addItem(u.user_sprite);
    scene->addItem(u.user_sprite->name_display);
}

void main_window::show_curren_sprite() {
    scene->clear();
    auto *text = new QGraphicsTextItem("Your character");
    scene->addItem(text);
    text->setPos(200, 100);
    auto *user_skin = new QGraphicsPixmapItem(
        QPixmap(":/images/" + QString(current_user.get_skin().c_str()) +
                "_sprite.png"));
    scene->addItem(user_skin);
    user_skin->setPos(250, 220);
}

void main_window::set_user_skin(const std::string &skin) {
    current_user.set_skin(skin);
}

void main_window::on_change_avatar_button_clicked() {
    // view->setEnabled(true);
    scene->clear();
    auto *text = new QGraphicsTextItem("Select a character by clicking on it");
    scene->addItem(text);
    text->setPos(200, 100);
    std::vector<std::string> characters = {
        "finn",  "gambol",        "miku",   "mushroom", "rafael",
        "sonic", "stormtroopers", "kermit", "pikachu"};
    for (int i = 0; i < 9; i++) {
        auto *skin = new sprite_for_choice(characters[i]);
        connect(skin, SIGNAL(add_curren_sprite()), this,
                SLOT(show_curren_sprite()));
        scene->addItem(skin);

        skin->setPos(150 + ((i % 3) * 100), 120 + ((i / 3) * 100));  // NOLINT
    }
}

void main_window::set_user_sprite() {
    current_user.user_sprite =
        new sprite(current_user.get_name(), current_user.get_skin());
    connect(current_user.user_sprite, SIGNAL(run_send_request(std::string)),
            current_session, SLOT(send_request(std::string)));
}

void main_window::on_headphones_check_stateChanged(int arg1) {
    if (!arg1) {  // if button is unpressed
        emit turn_head_on();
    } else {
        emit turn_head_off();
    }
}

void main_window::on_microphone_check_stateChanged(int arg1) {
    if (!arg1) {  // if button is unpressed
        emit turn_mic_on();
    } else {
        emit turn_mic_off();
    }
}
void main_window::initialize_user(client_user& u) {
    u.set_user_sprite();
    u.user_sprite->setPos(u.get_x(), u.get_y());
    u.user_sprite->name_display->setPlainText(u.get_name().c_str());
    u.user_sprite->name_display->setPos(u.get_x(), u.get_y() - 20);
}
