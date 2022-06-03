#include "client_socket.h"
#include "login.h"

client_socket::client_socket(const QHostAddress &host,
                             quint16 port,
                             QTcpSocket *ser,
                             network::queries_keeper *keeper,
                             QObject *parent)
    : tcp_socket(host, port, keeper, parent) {
    connect(ser, SIGNAL(readyRead()), this, SLOT(read()));
}

void client_processor::process() {
    auto raw_query = keeper->pop_parsed();
    query.ParseFromString(raw_query.first.toStdString());
    switch (query.ftype()) {
        case ChitChatMessage::Query_FeedbackType_NO_USER_FOUND:
            emit run_no_user();
            break;
        case ChitChatMessage::Query_FeedbackType_LOGIN_ALLOWED:
            emit run_successful_login(query);
            break;
        case ChitChatMessage::Query_FeedbackType_LOGIN_DENIED:
            emit run_wrong_password();
            break;
        case ChitChatMessage::Query_FeedbackType_USER_CREATED:
            emit run_successful_registration();
            break;
        case ChitChatMessage::Query_FeedbackType_USER_DUPLICATE:
            emit run_duplicate();
            break;
        case ChitChatMessage::Query_FeedbackType_CONNECTION_SUCCESS:
            // TODO: turn audio on
            emit run_connect_with_room(query);
            break;
        case ChitChatMessage::Query_FeedbackType_CONNECTION_EXISTS:
            emit run_already_connected();
            break;
        case ChitChatMessage::Query_FeedbackType_MOVED:
            // TODO: unify signatures to ChitChatMessage::Query as args
            emit run_change_position(query.user().name(),
                                     query.user().x_coord(),
                                     query.user().y_coord());
            break;
        case ChitChatMessage::Query_FeedbackType_DISCONNECTED:
            emit run_disconnect_roommate(query.user().name());
            break;
        case ChitChatMessage::Query_FeedbackType_SKIN_CHANGED:
            emit run_change_skin(query.user().skin());
            break;
        case ChitChatMessage::Query_FeedbackType_SCORE_CHANGED:
            // TODO
            break;
        case ChitChatMessage::Query_FeedbackType_DATABASE_ERROR:
            emit run_error();
            break;
        case ChitChatMessage::Query_FeedbackType_SKIN:
            break;
        case ChitChatMessage::Query_FeedbackType_NEW_USER_CONNECTED:
            emit run_connect_roommate(query);
            break;
    }
}
