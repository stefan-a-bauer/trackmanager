CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

project (trackmanager)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Qt4 REQUIRED)

# This adds the KDE data dir to CMAKE_MODULE_PATH. Only so the FindMarble.cmake is found.
find_package(KDE4 REQUIRED)
find_package(Marble REQUIRED)

find_package(SQLite REQUIRED)

include_directories(${MARBLE_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -std=c++11")

set(trackmanager_SRCS
    abstractimporter.cpp
    abstractmodel.cpp
    gpximporter.cpp
    main.cpp
    mainwindow.cpp
    model.cpp
)

set(trackmanager_HEADERS
    abstractimporter.h
    abstractmodel.h
    gpximporter.h
    mainwindow.h
    model.h
)

QT4_WRAP_CPP(trackmanager_HEADERS_MOC ${trackmanager_HEADERS})

INCLUDE(${QT_USE_FILE})

ADD_DEFINITIONS(${QT_DEFINITIONS})

add_executable(trackmanager ${trackmanager_SRCS} ${trackmanager_HEADERS_MOC})

target_link_libraries(trackmanager ${QT_LIBRARIES} ${MARBLE_LIBRARIES} ${SQLITE_LIBRARIES})
