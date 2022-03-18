#include "server.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    db::chitchat_database::local_connection();
    sv::controller aboba(QHostAddress::LocalHost, 1234);

    return a.exec();
}