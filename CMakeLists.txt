cmake_minimum_required(VERSION 2.8.11)

project(restinspector)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets)

include_directories(${Qt5Widgets_INCLUDE_DIRS})

add_definitions(${Qt5Widgets_DEFINITIONS})

add_executable(restinspector main.cpp RestInspector.cpp ResponseView.cpp CookiesTab.cpp BodyTab.cpp HeadersTab.cpp)

target_link_libraries(restinspector Qt5::Widgets)
