#ifndef LOGIN_H
#define LOGIN_H
#include <QDialog>
#include <QObject>
#include "client_socket.h"
#include "model.h"
#include "registration.h"

namespace Ui {
class login;
}

class login : public QDialog {
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    explicit login(model *current_session);

    ~login();

signals:
    void show_main_window();
    void show_registration_window();
    void run_send_request(const std::string &message);
    void run_initialize(std::string, std::string);

private slots:

    void on_show_password_check_box_stateChanged(int arg1);

    void on_log_in_button_clicked();

    void on_create_new_account_button_clicked();

    void show_login_window();

    void successful_login(const std::string &name);

    void wrong_password();

    void no_user();

    void error();

public slots:
    void remove_message();

private:
    Ui::login *ui;
    model *current_seccion = nullptr;
    client_processor *processor = nullptr;
    QTimer *timer;
    int TIME_FOR_MESSAGE = 1500;
};

#endif  // LOGIN_H
