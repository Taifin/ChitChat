#include "game_hangman.h"
#include <QDebug>
#include <QGridLayout>
#include <QLineEdit>
#include <random>
#include <vector>
#include "ui_game_hangman.h"
#include <QScreen>

game_hangman::game_hangman() : ui(new Ui::game_hangman) {
    ui->setupUi(this);
    setWindowTitle("HangMan");

    score = 0;
    game_start();

    this->setFixedSize(640, 420);

    // ui->letters->setSizeConstraint(QLayout::SetMinimumSize);

    for (int i = 0; i < 26; ++i) {
        letters[i] = new QToolButton(this);
        connect(letters[i], SIGNAL(clicked()), this, SLOT(letter_clicked()));
        letters[i]->setText(QString('a' + i));
        letters[i]->setFixedSize(60, 30);
        if (i < 24) {
            int row = i / 6;
            int col = i % 6;
            ui->letters->addWidget(letters[i], row, col);
        } else {
            ui->letters->addWidget(letters[i], 5, i - 22);
        }
    }
    for (int i = 0; i < 6; ++i) {
        QSpacerItem *item =
            new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Fixed);
        // ui->letters->addWidget(item);
    }

    std::string score_str = "Score: " + std::to_string(score);
    ui->score->setText(score_str.c_str());
    std::string theme_str = "Theme: " + theme;
    ui->theme->setText(theme_str.c_str());


    //QPixmap bkgnd(":/image/background.png");
    //bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, QColor(197, 240, 250));
    this->setPalette(palette);

    move(QGuiApplication::screens().at(0)->geometry().center() - frameGeometry().center());

    //start_button = new QToolButton(this);
    //exit_button = new QToolButton(this);
}

game_hangman::~game_hangman() {
    delete ui;
}

void game_hangman::paintEvent(QPaintEvent *) {
    painter.begin(this);

    painter.drawLine(500, 300, 600, 300);
    painter.drawLine(400, 100, 600, 100);
    painter.drawLine(580, 100, 580, 300);

    draw_man(mistakes);

    painter.end();
}

void game_hangman::draw_man(int step) {
    std::vector<std::vector<int>> parts{
        {450, 100, 450, 150}, {450, 180, 450, 250}, {450, 200, 470, 220},
        {450, 200, 440, 220}, {450, 250, 470, 270}, {450, 250, 440, 270}};
    if (step == -1) {
        for (int i = 1; i <= 5; i++) {
            if (i == 1) {
                painter.drawEllipse(430, 150 + 30, 30, 30);
            }
            painter.drawLine(parts[i][0], parts[i][1] + 30, parts[i][2],
                             parts[i][3] + 30);
        }
    }
    for (int i = 0; i <= step - 1; i++) {
        if (i == 0) {
            painter.drawEllipse(430, 150, 30, 30);
        }
        painter.drawLine(parts[i][0], parts[i][1], parts[i][2], parts[i][3]);
    }

    // painter.eraseRect(430,150, 470, 270);
}

void game_hangman::game_start() {
    mistakes = 0;
    game_status = 1;
    used_letters = "";
    word = random_word();
    print_word();
}

void game_hangman::print_letters() {
}

void game_hangman::print_word() {
    bool won = true;
    QString s = "";
    for (int i = 0; i < word.length(); i++) {
        if (used_letters.find(word[i]) == std::string::npos) {
            won = false;
            s += "_ ";
        } else {
            s += word[i];
            s += " ";
        }
    }
    ui->word->setText(s);
    if (won) {
        win();
    }
}

void game_hangman::win() {
    game_status = 0;
    mistakes = -1;
    update();
    for (int i = 0; i < used_letters.length(); i++) {
        letters[used_letters[i] - 'a']->show();
    }
    for (int i = 0; i < word.length(); i++) {
        letters[word[i] - 'a']->show();
    }
    ui->word->setText(word.c_str());
    ui->game_status->setText("<font color='red'>You win</font>");
    score += 10;
    std::string score_str = "Score: " + std::to_string(score);
    ui->score->setText(score_str.c_str());
    std::string theme_str = "Theme: " + theme;
    ui->score->setText(theme_str.c_str());
}

void game_hangman::lose() {
    game_status = 0;
    for (int i = 0; i < used_letters.length(); i++) {
        letters[used_letters[i] - 'a']->show();
    }
    for (int i = 0; i < word.length(); i++) {
        letters[word[i] - 'a']->show();
    }
    ui->word->setText(word.c_str());
    ui->game_status->setText("<font color='red'>You lose</font>");
}

void game_hangman::letter_clicked() {
    if (game_status) {
        QToolButton *letter = (QToolButton *)sender();
        char l = letter->text().toStdString()[0];
        letters[l - 'a']->hide();
        used_letters += l;
        if (word.find(l) == std::string::npos) {
            if (++mistakes >= 7) {
                mistakes = 6;
                lose();
            }
            update();
        } else {
            print_word();
        }
    }
}

std::string game_hangman::random_word() {
    std::vector<std::string> words{"aboba",      "calculus", "algorithm",
                                   "hangman",    "mem"
                                   };
    std::mt19937 mt(time(nullptr));
    return words[mt() % words.size()];
}
void game_hangman::start() {
    this->show();
}

extern "C" Q_DECL_EXPORT ChitChat_game *get_game() {
    return reinterpret_cast<ChitChat_game *>(new game_hangman());
}
