cmake_minimum_required(VERSION 3.5)

project(cgol LANGUAGES CXX)

enable_testing(true)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

find_package(Qt5 COMPONENTS Widgets Test REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS})

set(library_name ${PROJECT_NAME}_lib)

add_library(${library_name}
        cgol_window.cpp
        cgol_frame.cpp
        cgol_board.cpp
        cgol_logic.cpp)
target_link_libraries(${library_name} PUBLIC Qt5::Widgets)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(cgol PRIVATE ${library_name})

add_executable(test_gui test_gui.cpp)
add_test(test_gui test_gui)
target_link_libraries(test_gui PRIVATE Qt5::Test ${library_name})
