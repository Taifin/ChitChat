#include "rating.h"
#include "ui_rating.h"

rating::rating(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rating)
{
    ui->setupUi(this);
}

rating::~rating()
{
    delete ui;
}

void rating::on_back_to_room_button_clicked()
{
    this->hide();
}

