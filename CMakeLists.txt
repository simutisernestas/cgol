cmake_minimum_required(VERSION 3.5)

project(cgol LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_BINARY_DIR})

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(cgol
        main.cpp
        cgol_window.cpp
        cgol_window.hpp
        cgol.ui
        cgol_game.cpp
        cgol_game.hpp
        )

target_link_libraries(cgol PRIVATE Qt5::Widgets)
