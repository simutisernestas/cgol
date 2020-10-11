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

file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cpp include/*.hpp)
add_library(${library_name} ${sources})
target_link_libraries(${library_name} PUBLIC Qt5::Widgets)
target_include_directories(${library_name} PUBLIC include)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(cgol PRIVATE ${library_name})

add_executable(test_gui test/test_gui.cpp)
add_test(test_gui test_gui)
target_link_libraries(test_gui PRIVATE Qt5::Test ${library_name})

add_executable(test_board test/test_board.cpp)
add_test(test_board test_board)
target_link_libraries(test_board PRIVATE Qt5::Test ${library_name})

add_executable(test_game_logic test/test_game_logic.cpp)
add_test(test_game_logic test_game_logic)
target_link_libraries(test_game_logic PRIVATE Qt5::Test ${library_name})
