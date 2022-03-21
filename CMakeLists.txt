cmake_minimum_required(VERSION 3.10)
project(ChitChat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
include_directories(shared)
include_directories(client)
include_directories(server)

add_executable(ChitChat_server server/server.cpp server_testing.cpp server/state.cpp server/database.cpp shared/socket.cpp)
add_executable(ChitChat_client client/client_socket.cpp client/client_socket.h client/client_user.cpp client/client_user.h client/login.cpp client/login.h client/login.ui
        client/main.cpp client/main_window.cpp client/main_window.h client/main_window.ui client/registration.cpp client/registration.h client/registration.ui client/sprite.cpp client/sprite.h
        shared/socket.cpp shared/socket.h shared/user.h)
target_link_libraries(ChitChat_server Qt5::Widgets Qt5::Network -lpqxx -lpq)
target_link_libraries(ChitChat_client Qt5::Widgets Qt5::Network)

