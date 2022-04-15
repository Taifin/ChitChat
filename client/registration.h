#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>

namespace Ui {
class registration;
}

class registration : public QDialog {
    Q_OBJECT

public:
    explicit registration(QWidget *parent = nullptr);
    ~registration();

signals:
    void show_login_window_again();

private slots:
    void on_back_button_clicked();

    void on_confirm_button_clicked();

    void on_show_password_check_stateChanged(int arg1);

    void successful_registration();

    void duplicate();

    // void error();

private:
    Ui::registration *ui;
};

#endif  // REGISTRATION_H
