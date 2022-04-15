#include "registration.h"
#include "client_socket.h"
#include "ui_registration.h"
#include "user.h"

extern QTcpSocket*remote_server;
extern client_processor processor;

registration::registration(QWidget *parent)
    : QDialog(parent), ui(new Ui::registration) {
  ui->setupUi(this);
  this->setWindowTitle("ChitChat");

  connect(&processor, SIGNAL(run_successful_registration()), this,
          SLOT(successful_registration()));
  connect(&processor, SIGNAL(run_duplicate()), this, SLOT(duplicate()));
}

registration::~registration() { delete ui; }

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
    processor.prepare_query("register," + login + "," + password,
                            remote_server);
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
