cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_COMPILER /usr/bin/g++) 
set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CLANG_CXX_LANGUAGE_STAND = c++2a)

project(gameboy-emu VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# add_subdirectory(src)
# add_subdirectory(gui)
# add_subdirectory(include)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH /opt/homebrew/Cellar/qt)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SRC RELATIVE ${CMAKE_SOURCE_DIR} "src/**")
file(GLOB_RECURSE INCLUDE RELATIVE ${CMAKE_SOURCE_DIR} "include/**")
file(GLOB_RECURSE GUI RELATIVE ${CMAKE_SOURCE_DIR} "gui/**")

add_executable(gameboy-emu MACOSX_BUNDLE WIN32
    main.cpp
    ${INCLUDE}
    ${SRC}
    ${GUI}
)


target_include_directories(gameboy-emu
    PRIVATE include/ src/ gui/ $CMAKE_PREFIX_PATH
    /opt/homebrew/include/QtCore
    /opt/homebrew/Cellar/qt
)

target_compile_options(gameboy-emu PRIVATE -Wall -Wextra)

target_link_libraries(gameboy-emu PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(gameboy-emu PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(gameboy-emulator)
# endif()
