#ifndef MODEL_H
#define MODEL_H

#include <QApplication>
#include "client_socket.h"
#include "client_user.h"
#include "main_window.h"
#include "shared/socket.h"

class model
{
public:
    model();
    QTcpSocket *remote_server = new QTcpSocket();
    //client_user current_user("noname", "default_password");
    //std::map<std::string, client_user> users_in_the_room;
    //network::queries_keeper *keeper =
      //  new network::queries_keeper;  //Нужно delete keeper;

    //client_socket socket(QHostAddress::Any, 60000, remote_server, keeper, nullptr);
    //client_processor processor(keeper, socket);
    void set_curren_user(std::string name, std::string password);

};

#endif // MODEL_H
