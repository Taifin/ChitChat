#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include "socket.h"
#include <QObject>
#include <QString>
#include <QUdpSocket>

class client_socket : public network::udp_socket {
  Q_OBJECT
public:
  client_socket(const QHostAddress &host, quint16 port,
                network::queries_keeper *keeper, QObject *parent);
signals:
};

class client_processor : public network::query_processor {
  Q_OBJECT;

public:
  client_processor(network::queries_keeper *keeper, network::udp_socket &socket)
      : network::query_processor(keeper, socket) {}
  void process() override;
signals:
  void run_successful_login(const std::string &name);

  void run_wrong_password();

  void run_no_user();

  void run_error();

  void run_successful_registration();

  void run_duplicate();

  void run_already_connected();

  void run_connect_with_room(std::vector<std::string> data);

  void run_move(std::string username, int x, int y);

  void run_get();

  void run_change_position(std::string, int, int);

  // void run_initialize_users_in_the_room(std::vector<std::string> data);
};

#endif // CLIENT_SOCKET_H
