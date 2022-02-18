#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "login.h"

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

private:
    Ui::main_window *ui;
    login login_m;
};
#endif // MAIN_WINDOW_H
