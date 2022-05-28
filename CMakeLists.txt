cmake_minimum_required(VERSION 3.5)

project(ChitChat VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets Network Multimedia REQUIRED)
find_package(Protobuf REQUIRED)
include_directories(client)
include_directories(shared)
include_directories(server)
include_directories(games/arkanoid)
include_directories(games/hangman)

add_compile_definitions(LOCAL)
add_compile_definitions(SHARED)
set(CLIENT_SOURCES
        client/main.cpp
        client/model.h
        client/model.cpp
        client/main_window.cpp
        client/main_window.h
        client/main_window.ui
        client/login.h
        client/login.cpp
        client/login.ui
        shared/user.h
        client/registration.h
        client/registration.cpp
        client/registration.ui
        client/client_socket.h
        client/client_socket.cpp
        shared/socket.h
        shared/socket.cpp
        client/sprite.h
        client/sprite.cpp
        client/client_user.h
        client/client_user.cpp
        client/room.h
        client/room.cpp
        client/view.h
        client/view.cpp
        client/game_selection.cpp
        client/game_selection.ui
        client/game_selection.h
        client/voice_manager.cpp
        resources/resources.qrc
        shared/message.pb.cc
        shared/message.pb.h
        )

set(SERVER_SOURCES
        server/server.cpp
        run_server.cpp
        server/state.cpp
        server/database.cpp
        shared/socket.cpp
        shared/user.h
        shared/message.pb.cc
        shared/message.pb.h
        )

set(ARKANOID_SOURCES
        games/arkanoid/src/Ball.cpp
        games/arkanoid/src/Game.cpp
        games/arkanoid/src/Platform.cpp
        games/arkanoid/include/Game.h
        games/arkanoid/include/Ball.h
        games/arkanoid/include/Platform.h
        shared/abstract_game.h)

set(HANGMAN_SOURCES
        games/hangman/button.cpp
        games/hangman/game_hangman.cpp
        games/hangman/game_hangman.ui
        shared/abstract_game.h)

add_executable(ChitChatClient ${CLIENT_SOURCES} )
target_link_libraries(ChitChatClient Qt5::Widgets Qt5::Network Qt5::Multimedia -pthread -lprotobuf)

add_executable(ChitChatServer ${SERVER_SOURCES})
target_link_libraries(ChitChatServer PRIVATE Qt5::Widgets Qt5::Network Qt5::Multimedia -lpqxx -lpq -pthread -lprotobuf)

add_library(Arkanoid SHARED ${ARKANOID_SOURCES})
target_link_libraries(Arkanoid Qt5::Widgets)

add_library(Hangman SHARED ${HANGMAN_SOURCES})
target_link_libraries(Hangman Qt5::Widgets)
