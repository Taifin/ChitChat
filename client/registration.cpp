#include "registration.h"
#include "ui_registration.h"
#include "database.h"
#include "user.h"

registration::registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registration)
{
    ui->setupUi(this);
    this->setWindowTitle("ChitChat");
}

registration::~registration()
{
    delete ui;
}

void registration::on_back_button_clicked()
{
    this->hide();
    emit show_login_window_again();
}

void registration::on_confirm_button_clicked()
{
    std::string login, password, confirm_password;
    login = (ui->name_line_edit->text()).toStdString();
    password = ui->password_line_edit->text().toStdString();
    confirm_password = ui-> confirm_line_edit->text().toStdString();

    if (password != confirm_password){
        ui->information_label->setText("Passwords don't match");
    }
    else{
        User user(login, password);
        try{
            if (db::chitchat_database::create_user(&user)){
                this->hide();
                emit show_login_window_again();
            }
            else{
                ui->information_label->setText("Name already in use. Please choose another one");
            }
        }
        catch(...){
            ui->information_label->setText("Something go wrong");
        }
    }
}


void registration::on_show_password_check_stateChanged(int arg1)
{
    if (arg1){
        ui->password_line_edit->QLineEdit::setEchoMode(QLineEdit::Normal);
        ui->confirm_line_edit->QLineEdit::setEchoMode(QLineEdit::Normal);
    }
    else{
        ui->password_line_edit->QLineEdit::setEchoMode(QLineEdit::Password);
        ui->confirm_line_edit->QLineEdit::setEchoMode(QLineEdit::Password);
    }
}

