cmake_minimum_required(VERSION 3.5)

project(ChitChat VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Network)

set(PROJECT_SOURCES
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
            resources/resources.qrc

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ChitChat
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ChitChat APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ChitChat SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ChitChat
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ChitChat PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt5::Network -lpqxx -lpq -pthread)


set_target_properties(ChitChat PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ChitChat)
endif()
