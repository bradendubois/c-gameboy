cmake_minimum_required(VERSION 3.5)

project(gameboy-emu VERSION 0.1 LANGUAGES CXX)

set(CMAKE_C_COMPILER /usr/bin/g++) 
set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CLANG_CXX_LANGUAGE_STAND = c++2a)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH /opt/homebrew/Cellar/qt)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

find_package(Qt6 REQUIRED COMPONENTS Multimedia)
find_package(Qt6 REQUIRED COMPONENTS MultimediaWidgets)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SRC RELATIVE ${CMAKE_SOURCE_DIR} "src/**")
file(GLOB_RECURSE INCLUDE RELATIVE ${CMAKE_SOURCE_DIR} "include/**")

add_executable(gameboy-emu MACOSX_BUNDLE WIN32
    main.cpp ${INCLUDE} ${SRC}
)

target_include_directories(gameboy-emu
    PRIVATE include/ src/ $CMAKE_PREFIX_PATH
    /opt/homebrew/include/QtCore
    /opt/homebrew/Cellar/qt
)

target_compile_options(gameboy-emu PRIVATE -Wall -Wextra)

target_link_libraries(gameboy-emu PRIVATE Qt6::Widgets Qt6::Multimedia Qt6::MultimediaWidgets)

set_target_properties(gameboy-emu PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
