#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include "login.h"
#include "sprite.h"
#include "room.h"
#include "model.h"

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

    client_user current_user;
    std::map<std::string, client_user> users_in_the_room;

    model *current_session = nullptr;

    void set_user_sprite();


    ~main_window();

signals:
    void run_send_request(const std::string &message);

private slots:
    void on_change_avatar_button_clicked();

    void show_after_auth();

    void on_connect_button_clicked();

    void already_connected();

    void connect_with_room(std::vector<std::string> data);

    void user_changed_position(std::string name, int x, int y);

    void roommate_disconnect(const std::string &roommate_name);

    void roommate_connect(const std::string &roommate_name);

    void show_curren_sprite();



private:
    Ui::main_window *ui;
    room *scene;
    QGraphicsView *view;
    sprite_of_object *game_machine = new sprite_of_object("game_machine");


};
#endif  // MAIN_WINDOW_H
