#include "login.h"
#include <QLineEdit>
#include <QMetaType>
#include "main_window.h"
#include "shared/user.h"
#include "ui_login.h"

login::login(QWidget *parent) : QDialog(parent), ui(new Ui::login) {
    ui->setupUi(this);
    this->setWindowTitle("ChitChat");
}

login::~login() {
    delete ui;
}

void login::on_show_password_check_box_stateChanged(int arg1) {
    if (arg1) {
        ui->password_line_edit->QLineEdit::setEchoMode(QLineEdit::Normal);
    } else {
        ui->password_line_edit->QLineEdit::setEchoMode(QLineEdit::Password);
    }
}

void login::on_log_in_button_clicked() {
    std::string login, password;
    login = (ui->login_line_edit->text().toStdString());
    password = ui->password_line_edit->text().toStdString();
    user u(login, password, "aboba");
    emit run_send_request(u.serialize(ChitChatMessage::Query_RequestType_LOGIN));
}

void login::on_create_new_account_button_clicked() {
    this->hide();
    emit show_registration_window();
}

void login::show_login_window() {
    this->show();
}

void login::successful_login(const ChitChatMessage::Query &q) {
    this->hide();
    emit run_initialize(q.user().name(), q.user().skin());
    emit show_main_window();
}

void login::wrong_password() {
    ui->information_label->setText("Wrong password");
}

void login::no_user() {
    ui->information_label->setText("User is not found");
}

void login::error() {
    ui->information_label->setText("Something go wrong");
}
