CMAKE_MINIMUM_REQUIRED (VERSION 2.8.11)

project (trackmanager)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Qt5 COMPONENTS Widgets Xml Sql REQUIRED)
find_package(Marble REQUIRED)
find_package(SQLite REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/model
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Xml_INCLUDE_DIRS}
    ${MARBLE_INCLUDE_DIR}
    ${MARBLE_INCLUDE_DIR}/marble
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -fexceptions -std=c++11")

set(trackmanager_SRCS
    model/Activity.cpp
    model/Box.cpp
    model/Entity.cpp
    model/DescribedEntity.cpp
    model/Gear.cpp
    model/Highlight.cpp
    model/NamedEntity.cpp
    model/Point.cpp
    model/Position.cpp
    model/Tour.cpp
    model/Track.cpp
    model/TrackPoint.cpp
    model/WayPoint.cpp
    ui/Cache.cpp
    ui/ControlView.cpp
    ui/Layer.cpp
    ui/mainwindow.cpp
    ui/tools.cpp
    Exception.cpp
    abstractimporter.cpp
    gpximporter.cpp
    main.cpp
    Repository.cpp
)

set(trackmanager_HEADERS
    model/Activity.h
    model/Box.h
    model/DescribedEntity.h
    model/Entity.h
    model/NamedEntity.h
    model/Gear.h
    model/Highlight.h
    model/Point.h
    model/Position.h
    model/Tour.h
    model/Track.h
    model/TrackPoint.h
    model/WayPoint.h
    ui/Cache.h
    ui/ControlView.h
    ui/Layer.h
    ui/mainwindow.h
    ui/tools.h
    abstractimporter.h
    Exception.h
    gpximporter.h
    Repository.h
    types.h
)

add_executable(trackmanager ${trackmanager_SRCS})

target_link_libraries(
    trackmanager
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Xml_LIBRARIES}
    ${Qt5Sql_LIBRARIES}
    ${MARBLE_LIBRARIES}
    ${SQLITE_LIBRARIES})
