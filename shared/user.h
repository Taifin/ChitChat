#ifndef CHITCHAT_USER_H
#define CHITCHAT_USER_H

#include <utility>
#include "QObject"
#include "QDebug"
#include "string"
#include "message.pb.h"

struct point {
    int x;
    int y;
};

class user : public QObject {
    Q_OBJECT

    std::string username;
    std::string password;
    std::string skin = "miku";
    point coords;

public:
    explicit user(std::string uname,
                  std::string upwd,
                  std::string skin_name,
                  int x = 0,
                  int y = 0)
        : username(std::move(uname)),
          password(std::move(upwd)),
          skin(std::move(skin_name)),
          coords({x, y}){};

    user(const user &other)
        : username(other.username),
          password(other.password),
          coords(other.coords),
          skin(other.skin) {
    }

    virtual ~user() = default;

    [[nodiscard]] const std::string &name() const {
        return username;
    }

    [[nodiscard]] const std::string &pwd() const {
        return password;
    }

    [[nodiscard]] point get_coords() const {
        return coords;
    }

    [[nodiscard]] int get_x() const {
        return coords.x;
    }

    [[nodiscard]] int get_y() const {
        return coords.y;
    }

    void set_coords(int x, int y) {
        coords = {x, y};
    }

//    user &operator=(const user &other) {
//        username = other.username;
//        password = other.password;
//        coords = other.coords;
//        return *this;
//    }

    [[nodiscard]] const std::string& get_name() const {
        return username;
    }

    [[nodiscard]] std::string get_skin() const {
        return skin;
    }

    [[nodiscard]] ChitChatMessage::Query serialize(ChitChatMessage::Query::RequestType type) const {
        ChitChatMessage::Query query;
        ChitChatMessage::Query_User user;
        user.set_name(username);
        user.set_password(password);
        user.set_skin(skin);
        user.set_x_coord(coords.x);
        user.set_y_coord(coords.y);
        query.set_allocated_user(&user);
        query.set_rtype(type);
        return query;
    }

    void parse(const ChitChatMessage::Query& query) {
        username = query.user().name();
        password = query.user().password();
        skin = query.user().skin();
        coords = {query.user().x_coord(), query.user().y_coord()};
    }

private slots:
    void initialize(const std::string &name, const std::string &skin_type) {
        skin = skin_type;
        username = name;
        qDebug() << get_skin().c_str() << get_name().c_str();
    }
};

#endif  // CHITCHAT_USER_H
