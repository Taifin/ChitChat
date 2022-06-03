#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include "message.pb.h"
#include "shared/user.h"

namespace Ui {
class registration;
}

class registration : public QDialog {
    Q_OBJECT

public:
    explicit registration(QWidget *parent = nullptr);
    ~registration() override;

signals:
    void show_login_window_again();
    void run_send_request(const ChitChatMessage::Query &message);

private slots:

    void on_back_button_clicked();

    void on_confirm_button_clicked();

    void on_show_password_check_stateChanged(int arg1);

    void successful_registration();

    void duplicate();

public slots:
    void remove_message();

private:
    Ui::registration *ui;
    QTimer *timer;
    int TIME_FOR_MESSAGE = 1500;
};

#endif  // REGISTRATION_H
