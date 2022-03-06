#include "login.h"
#include "ui_login.h"
#include "database.h"
#include "main_window.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    connect(&registration_m, SIGNAL(show_login_window_again()), this, SLOT(show_login_window()));
    ui->setupUi(this);
    this->setWindowTitle("ChitChat");
}

login::~login()
{
    delete ui;
}

void login::on_show_password_check_box_stateChanged(int arg1)
{
    if (arg1){
        ui->password_line_edit->QLineEdit::setEchoMode(QLineEdit::Normal);
    }
    else{
        ui->password_line_edit->QLineEdit::setEchoMode(QLineEdit::Password);
    }
}


void login::on_log_in_button_clicked()
{
    std::string login, password;
    login = (ui->login_line_edit->text()).toStdString();
    password = ui->password_line_edit->text().toStdString();

    try{
        if (db::chitchat_database::authorize(login, password)){
            this->hide();
            emit show_main_window();
        }
        else{
            ui->information_label->setText("Wrong password");
        }
    }
    catch(db::no_user_found &){
        ui->information_label->setText("User is not found");
    }
    catch(...){
        ui->information_label->setText("Something go wrong");
    }
}


void login::on_create_new_account_button_clicked()
{
    this->hide();
    registration_m.show();
}

void login::show_login_window(){
    this->show();
}
