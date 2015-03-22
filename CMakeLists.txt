project (trackmanager)
find_package(KDE4 REQUIRED)
include (KDE4Defaults)
include_directories(${KDE4_INCLUDES})
set(trackmanager_SRCS main.cpp)
kde4_add_executable(trackmanager ${trackmanager_SRCS})
target_link_libraries(trackmanager ${KDE4_KDEUI_LIBS})
install(TARGETS trackmanager  ${INSTALL_TARGETS_DEFAULT_ARGS})

