#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "login.h"
#include <QGraphicsScene>
#include "sprite.h"

QT_BEGIN_NAMESPACE
namespace Ui { class main_window; }
QT_END_NAMESPACE

class main_window : public QMainWindow
{
    Q_OBJECT

public:
    void start();

    main_window(QWidget *parent = nullptr);
    ~main_window();

private slots:
    void show_after_auth();

    void on_connect_button_clicked();

    void already_connected();

    void connect_with_room(std::vector<std::string> data);

    //void initialize_users_in_the_room(std::vector<std::string> data);

private:
    Ui::main_window *ui;
    login login_m;
    QGraphicsScene *scene;
    //sprite *sprite_current_user;
};
#endif // MAIN_WINDOW_H
