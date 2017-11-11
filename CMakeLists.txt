cmake_minimum_required(VERSION 3.9)
project(tree-o-grow)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5Widgets REQUIRED)

#qt5_wrap_ui(UI_HEADERS MainWindow.ui)

add_executable(tree-o-grow main.cpp MainWindow.cpp ${UI_HEADERS})
qt5_use_modules(tree-o-grow Widgets)
