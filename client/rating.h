#ifndef RATING_H
#define RATING_H

#include <QWidget>

namespace Ui {
class rating;
}

class rating : public QWidget
{
    Q_OBJECT

public:
    explicit rating(QWidget *parent = nullptr);

    ~rating();

private slots:
    void on_exit_button_clicked();

    void on_back_to_room_button_clicked();

private:
    Ui::rating *ui;
};

#endif // RATING_H
