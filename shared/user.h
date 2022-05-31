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
    point coords{0, 0};

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

    user() = default;

    ~user() override = default;

    [[nodiscard]] const std::string &get_name() const {
        return username;
    }

    [[nodiscard]] const std::string &get_password() const {
        return password;
    }

    [[nodiscard]] int get_x() const {
        return coords.x;
    }

    [[nodiscard]] int get_y() const {
        return coords.y;
    }

    [[nodiscard]] std::string get_skin() const {
        return skin;
    }

    void set_coords(int x, int y) {
        coords = {x, y};
    }

    void set_skin(const std::string& skin_name) {
        skin = skin_name;
    }

    [[nodiscard]] ChitChatMessage::Query serialize(ChitChatMessage::Query::RequestType type) const {
        ChitChatMessage::Query query;
        query.mutable_user()->set_name(username);
        query.mutable_user()->set_password(password);
        query.mutable_user()->set_skin(skin);
        query.mutable_user()->set_x_coord(coords.x);
        query.mutable_user()->set_y_coord(coords.y);
        query.set_rtype(type);
        return std::move(query);
    }

    [[nodiscard]] ChitChatMessage::Query serialize(ChitChatMessage::Query::FeedbackType type) const {
        ChitChatMessage::Query query;
        query.mutable_user()->set_name(username);
        query.mutable_user()->set_password(password);
        query.mutable_user()->set_skin(skin);
        query.mutable_user()->set_x_coord(coords.x);
        query.mutable_user()->set_y_coord(coords.y);
        query.set_ftype(type);
        return query;
    }

    void parse(const ChitChatMessage::Query& query) {
        username = query.user().name();
        password = query.user().password();
        skin = query.user().skin();
        coords = {query.user().x_coord(), query.user().y_coord()};
    }

    void parse(const ChitChatMessage::Query_User& user) {
        username = user.name();
        password = user.password();
        skin = user.skin();
        coords = {user.x_coord(), user.y_coord()};
    }

private slots:
    void initialize(const std::string &name, const std::string &skin_type) {
        skin = skin_type;
        username = name;
        qDebug() << get_skin().c_str() << get_name().c_str();
    }
};

#endif  // CHITCHAT_USER_H
