cmake_minimum_required(VERSION 3.5)

project(gameboy-emulator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH /opt/homebrew/Cellar/qt)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

qt_add_executable(gameboy-emu MACOSX_BUNDLE WIN32
    include/cpu.h
    include/gameboy.h
    include/mainwindow.h
    main.cpp
    src/alu.cpp
    src/instructions.cpp
    src/mmu.cpp
    src/mainwindow.cpp
    src/mainwindow.ui
)

# set(PROJECT_SOURCES
#         main.cpp
#         src/mainwindow.cpp
#         include/mainwindow.h
#         src/mainwindow.ui
# )

# if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#     qt_add_executable(gameboy-emulator
#         MANUAL_FINALIZATION
#         ${PROJECT_SOURCES}
#     )
# # Define target properties for Android with Qt 6 as:
# #    set_property(TARGET gameboy-emulator APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
# #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
# else()
#     if(ANDROID)
#         add_library(gameboy-emulator SHARED
#             ${PROJECT_SOURCES}
#         )
# # Define properties for Android with Qt 5 after find_package() calls as:
# #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#     else()
#         add_executable(gameboy-emulator
#             ${PROJECT_SOURCES}
#         )
#     endif()
# endif()

target_link_libraries(gameboy-emu PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_compile_options(gameboy-emu PRIVATE -Wall -Wextra -Wpedantic -Werror)

# set_target_properties(gameboy-emulator PROPERTIES
#     MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(gameboy-emulator)
# endif()
