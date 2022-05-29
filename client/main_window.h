#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QCoreApplication>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QTimer>
#include "game_selection.h"
#include "login.h"
#include "model.h"
#include "room.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class main_window;
}
QT_END_NAMESPACE

class main_window : public QMainWindow {
    Q_OBJECT

public:
    void start();

    main_window(QWidget *parent = nullptr);

    void set_user_skin(const std::string &skin);
    void set_sprite_name(sprite *sprite);

    client_user current_user;
    std::map<std::string, client_user> users_in_the_room;

    model *current_session = nullptr;

    void set_user_sprite();

    ~main_window();

public slots:
    void remove_message();

signals:
    void run_send_request(const std::string &message);

    void turn_mic_on();

    void turn_mic_off();

    void turn_head_on();

    void turn_head_off();

    void stop_thread();

private slots:
    void on_change_avatar_button_clicked();

    void show_after_auth();

    void on_connect_button_clicked();

    void already_connected();

    void connect_with_room(std::vector<std::string> data);

    void user_changed_position(const std::string &name, int x, int y);

    void roommate_disconnect(const std::string &roommate_name);

    void roommate_connect(const std::string &roommate_name);

    void show_curren_sprite();

    void on_microphone_check_stateChanged(int arg1);

    void on_headphones_check_stateChanged(int arg1);

    void send_skin(const std::string &skin);

private:
    Ui::main_window *ui;
    room *scene;
    QGraphicsView *view;
    QTimer *timer;
    int TIME_FOR_MESSAGE = 1500;
    QFont font;
    QPen pen;
    QBrush brush;
};
#endif  // MAIN_WINDOW_H
