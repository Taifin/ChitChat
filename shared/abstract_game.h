#ifndef CHITCHAT_ABSTRACT_GAME_H
#define CHITCHAT_ABSTRACT_GAME_H

#include "QMainWindow"

#ifdef SHARED
#define Q_EXPORT Q_DECL_EXPORT
#else
#define Q_EXPORT Q_DECL_IMPORT
#endif

class Q_DECL_EXPORT ChitChat_game : public QMainWindow {
    Q_OBJECT

public:
    virtual void start() = 0;
};

#endif  // CHITCHAT_ABSTRACT_GAME_H