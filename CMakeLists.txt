cmake_minimum_required(VERSION 3.10)
project(ChitChat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)
add_compile_definitions(LOCAL)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Network)
include_directories(client)
include_directories(shared)
include_directories(server)

set(PROJECT_SOURCES
        client/main.cpp
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
        )

add_executable(ChitChat_server server/server.cpp server_testing.cpp server/state.cpp server/database.cpp shared/socket.cpp)
target_link_libraries(ChitChat_server Qt5::Widgets Qt5::Network -lpqxx -lpq -pthread)


add_executable(ChitChat ${PROJECT_SOURCES} )
target_link_libraries(ChitChat PRIVATE Qt5::Widgets Qt5::Network -lpqxx -lpq -pthread)