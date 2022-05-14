#include "registration.h"
#include "ui_registration.h"
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
    ui->stormtroopers_label->setPixmap(QPixmap(":/images/stormtroopers_sprite.png"));
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
    } else {
        emit run_send_request("register," + login + "," + password);
        //TODO: передавать на сервер информацию о выборе
        if (ui->finn_radio_button->isChecked()){
            qDebug() << "finn";
        } else if (ui->gambol_radio_button->isChecked()) {
            qDebug() << "gambol";
        } else if (ui->kermit_radio_button->isChecked()) {
            qDebug() << "kertmit";
        } else if (ui->miku_radio_button->isChecked()) {
            qDebug() << "miku";
        } else if (ui->mushroom_radio_button->isChecked()) {
            qDebug() << "mushrom";
        } else if (ui->pikachu_radio_button->isChecked()) {
            qDebug() << "pikachu";
        } else if (ui->rafael_radio_button->isChecked()) {
            qDebug() << "rafael";
        } else if (ui->sonic_radio_button->isChecked()) {
            qDebug() << "sonic";
        } else if (ui->stormtroopers_radio_button->isChecked()) {
            qDebug() << "rafael";
        }
    }
}

void registration::successful_registration() {
    this->hide();
    emit show_login_window_again();
}

void registration::duplicate() {
    ui->information_label->setText(
        "Name already in use. Please choose another one");
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
