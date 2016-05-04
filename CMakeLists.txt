cmake_minimum_required(VERSION 2.8.11)

project(restinspector)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Boost)
find_package(Qt5Core)
find_package(Qt5Xml)
find_package(Qt5Widgets)
find_package(Qt5Network)

include_directories(${Boost_INCLUDE_DIRS} ${Qt5Xml_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS})

add_definitions(${Qt5Widgets_DEFINITIONS})

add_executable(restinspector main.cpp RestInspector.cpp ResponseView.cpp CookiesTab.cpp BodyTab.cpp HeadersTab.cpp)

target_link_libraries(restinspector ${Boost_LIBRARIES} Qt5::Xml Qt5::Core Qt5::Widgets Qt5::Network)
