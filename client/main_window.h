#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include "game_selection.h"
#include "login.h"
#include "model.h"
#include "room.h"
#include "message.pb.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class main_window;
}
QT_END_NAMESPACE

class main_window : public QMainWindow {
    Q_OBJECT

public:
    void start();

    explicit main_window(QWidget *parent = nullptr);

    void set_user_skin(const std::string &skin);

    client_user current_user;
    std::map<std::string, client_user> users_in_the_room;

    model *current_session = nullptr;

    void set_user_sprite();

    ~main_window() override;

signals:
    void run_send_request(const ChitChatMessage::Query &message);

    void turn_mic_on();

    void turn_mic_off();

    void turn_head_on();

    void turn_head_off();

private slots:
    void on_change_avatar_button_clicked();

    void show_after_auth();

    void on_connect_button_clicked();

    void already_connected();

    void connect_with_room(const ChitChatMessage::Query &data);

    void user_changed_position(const std::string &name, int x, int y);

    void roommate_disconnect(const std::string &roommate_name);

    void roommate_connect(const ChitChatMessage::Query &roommate_data);

    void show_curren_sprite();

    void on_microphone_check_stateChanged(int arg1);

    void on_headphones_check_stateChanged(int arg1);

private:
    Ui::main_window *ui;
    room *scene;
    QGraphicsView *view;

    void initialize_user(client_user& u);
};
#endif  // MAIN_WINDOW_H
