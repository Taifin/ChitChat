#ifndef LOGIN_H
#define LOGIN_H
#include <QDialog>
#include "registration.h"
#include "client_socket.h"
#include <QObject>


namespace Ui {
class login;
}

class login : public QDialog {
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);

    ~login();

signals:
    void show_main_window();

private slots:

    void on_show_password_check_box_stateChanged(int arg1);

    void on_log_in_button_clicked();

    void on_create_new_account_button_clicked();

    void show_login_window();

    void successful_login(const std::string& name);

    void wrong_password();

    void no_user();

    void error();

private:
    Ui::login *ui;
    registration registration_m;
};

#endif  // LOGIN_H
