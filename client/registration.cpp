#include "registration.h"
#include <QTimer>
#include <vector>
#include "client_socket.h"
#include "shared/user.h"
#include "ui_registration.h"

registration::registration(QWidget *parent)
    : QDialog(parent), ui(new Ui::registration) {
    ui->setupUi(this);
    this->setWindowTitle("ChitChat");

    ui->finn_label->setPixmap(QPixmap(":/images/finn_sprite.png"));
    ui->sonic_label->setPixmap(QPixmap(":/images/sonic_sprite.png"));
    ui->rafael_label->setPixmap(QPixmap(":/images/rafael_sprite.png"));
    ui->kermit_label->setPixmap(QPixmap(":/images/kermit_sprite.png"));
    ui->gambol_label->setPixmap(QPixmap(":/images/gambol_sprite.png"));
    ui->pikachu_label->setPixmap(QPixmap(":/images/pikachu_sprite.png"));
    ui->miku_label->setPixmap(QPixmap(":/images/miku_sprite.png"));
    ui->mushroom_label->setPixmap(QPixmap(":/images/mushroom_sprite.png"));
    ui->stormtroopers_label->setPixmap(
        QPixmap(":/images/stormtroopers_sprite.png"));

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(remove_message()));
}

registration::~registration() {
    delete ui;
}

void registration::on_back_button_clicked() {
    this->hide();
    emit show_login_window_again();
}

void registration::on_confirm_button_clicked() {
    std::string login, password, confirm_password;
    login = (ui->name_line_edit->text()).toStdString();
    password = ui->password_line_edit->text().toStdString();
    confirm_password = ui->confirm_line_edit->text().toStdString();

    if (password != confirm_password) {
        ui->information_label->setText("Passwords don't match");
    } else if (login.length() == 0) {
        ui->information_label->setText("You haven't entered a login");
        timer->start(TIME_FOR_MESSAGE);
    } else if (password.length() < 6) {
        ui->information_label->setText(
            "This password is too short. (At least 6 symbols)");
        timer->start(TIME_FOR_MESSAGE);
    } else {
        emit run_send_request("register," + login + "," + password);
        if (ui->finn_radio_button->isChecked()) {
            emit run_send_request("register," + login + "," + password + "," +
                                  "finn");
        } else if (ui->gambol_radio_button->isChecked()) {
            emit run_send_request("register," + login + "," + password + "," +
                                  "gambol");
        } else if (ui->kermit_radio_button->isChecked()) {
            emit run_send_request("register," + login + "," + password + "," +
                                  "kermit");
        } else if (ui->miku_radio_button->isChecked()) {
            emit run_send_request("register," + login + "," + password + "," +
                                  "miku");
        } else if (ui->mushroom_radio_button->isChecked()) {
            emit run_send_request("register," + login + "," + password + "," +
                                  "myshroom");
        } else if (ui->pikachu_radio_button->isChecked()) {
            emit run_send_request("register," + login + "," + password + "," +
                                  "pikachu");
        } else if (ui->rafael_radio_button->isChecked()) {
            emit run_send_request("register," + login + "," + password + "," +
                                  "rafael");
        } else if (ui->sonic_radio_button->isChecked()) {
            emit run_send_request("register," + login + "," + password + "," +
                                  "sonic");
        } else if (ui->stormtroopers_radio_button->isChecked()) {
            emit run_send_request("register," + login + "," + password + "," +
                                  "stormtroopers");
        }
    }
}

void registration::successful_registration() {
    this->close();
    emit show_login_window_again();
}

void registration::duplicate() {
    ui->information_label->setText(
        "Name already in use. Please choose another one");
    timer->start(TIME_FOR_MESSAGE);
}

void registration::remove_message() {
    ui->information_label->clear();
}

void registration::on_show_password_check_stateChanged(int arg1) {
    if (arg1) {
        ui->password_line_edit->QLineEdit::setEchoMode(QLineEdit::Normal);
        ui->confirm_line_edit->QLineEdit::setEchoMode(QLineEdit::Normal);
    } else {
        ui->password_line_edit->QLineEdit::setEchoMode(QLineEdit::Password);
        ui->confirm_line_edit->QLineEdit::setEchoMode(QLineEdit::Password);
    }
}
