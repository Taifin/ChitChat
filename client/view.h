#ifndef VIEW_H
#define VIEW_H
#include <QObject>
#include "login.h"
#include "main_window.h"
#include "model.h"
#include "registration.h"

class view : public QObject {
    Q_OBJECT

public:
    view();

    model current_session;

    main_window main_process;
    registration registration_process;
    login login_process;

    void start();

    ~view() = default;
};

#endif  // VIEW_H
