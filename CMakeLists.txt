cmake_minimum_required(VERSION 3.5)

project(ChitChat VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)
include_directories(client)
include_directories(shared)
include_directories(server)

add_compile_definitions(LOCAL)
#add_compile_definitions(NOLOCAL)

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
        resources/resources.qrc
        )

set(SERVER_SOURCES
        server/server.cpp
        server_testing.cpp
        server/state.cpp
        server/database.cpp
        shared/socket.cpp
        )

add_executable(ChitChatClient ${CLIENT_SOURCES} )
target_link_libraries(ChitChatClient Qt5::Widgets Qt5::Network -pthread)

add_executable(ChitChatServer ${SERVER_SOURCES})
target_link_libraries(ChitChatServer PRIVATE Qt5::Widgets Qt5::Network -lpqxx -lpq -pthread)
