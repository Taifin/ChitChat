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
target_link_libraries(ChitChat_server Qt5::Widgets Qt5::Network -lpqxx -lpq -pthread)
