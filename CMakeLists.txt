CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
project (trackmanager)
find_package(KDE4 REQUIRED)
find_package(Marble REQUIRED)
include (KDE4Defaults)
include_directories(${KDE4_INCLUDES})
include_directories(${MARBLE_INCLUDE_DIR})
set(trackmanager_SRCS
  main.cpp
  mainwindow.cpp)
kde4_add_executable(trackmanager ${trackmanager_SRCS})
target_link_libraries(trackmanager ${KDE4_KDEUI_LIBS} ${MARBLE_LIBRARIES})
install(TARGETS trackmanager  ${INSTALL_TARGETS_DEFAULT_ARGS})

