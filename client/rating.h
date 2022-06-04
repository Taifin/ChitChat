#ifndef RATING_H
#define RATING_H

#include <QWidget>
#include <QScreen>
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

    std::vector<std::pair<int, std::string>> hangman_rating;
    std::vector<std::pair<int, std::string>> arkanoid_rating;

    ~rating() override;

private slots:

    void on_back_to_room_button_clicked();

    void change_score(const std::string &name,
                      int score,
                      const std::string &game) {
        if (game == "hangman") {
            hangman_rating.push_back({score, name});
        }
        if (game == "arkanoid") {
            arkanoid_rating.push_back({score, name});
        }
    };

private:
    Ui::rating *ui;

    std::vector<std::string> current_users;
};

#endif  // RATING_H
