#include "main_window.h"
#include "database.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    db::chitchat_database::local_connection();
    db::chitchat_database::debug_create_table();

    QApplication a(argc, argv);
    main_window w;
    w.start();

    return a.exec();
}
