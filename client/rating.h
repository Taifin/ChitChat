#ifndef RATING_H
#define RATING_H

#include <QWidget>
#include <algorithm>
#include <string>
#include <vector>

namespace Ui {
class rating;
}

class rating : public QWidget {
    Q_OBJECT

public:
    explicit rating(QWidget *parent = nullptr);
    void update_rating();

    ~rating();

private slots:

    void on_back_to_room_button_clicked();

private:
    Ui::rating *ui;
    std::vector<std::pair<int, std::string>> hangman_rating;
    std::vector<std::pair<int, std::string>> arkanoid_rating;
};

#endif  // RATING_H
