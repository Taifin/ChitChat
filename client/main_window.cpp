#include "main_window.h"
#include "./ui_main_window.h"

main_window::main_window(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::main_window) {
    connect(&login_m, SIGNAL(show_main_window()), this,
            SLOT(show_after_auth()));
    ui->setupUi(this);
    this->setWindowTitle("ChitChat");
}

void main_window::start() {
    login_m.show();
}

void main_window::show_after_auth() {
    this->show();
};

main_window::~main_window() {
    delete ui;
}