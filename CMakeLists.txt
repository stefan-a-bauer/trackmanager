CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

project (trackmanager)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Qt4 COMPONENTS QtCore QtGUI QtSql QtXml REQUIRED)

# This adds the KDE data dir to CMAKE_MODULE_PATH. Only so the FindMarble.cmake is found.
find_package(KDE4 REQUIRED)
find_package(Marble REQUIRED)

find_package(SQLite REQUIRED)

include_directories(${MARBLE_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -std=c++11")

set(trackmanager_SRCS
    model/Activity.cpp
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
    Exception.cpp
    abstractimporter.cpp
    gpximporter.cpp
    main.cpp
    mainwindow.cpp
    Repository.cpp
)

set(trackmanager_HEADERS
    model/Activity.h
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
    abstractimporter.h
    Exception.h
    gpximporter.h
    mainwindow.h
    Repository.h
    types.h
)

QT4_WRAP_CPP(trackmanager_HEADERS_MOC ${trackmanager_HEADERS})

INCLUDE(${QT_USE_FILE})

ADD_DEFINITIONS(${QT_DEFINITIONS})

add_executable(trackmanager ${trackmanager_SRCS} ${trackmanager_HEADERS_MOC})

target_link_libraries(trackmanager ${QT_LIBRARIES} ${MARBLE_LIBRARIES} ${SQLITE_LIBRARIES})
