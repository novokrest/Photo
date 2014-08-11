cmake_minimum_required(VERSION 2.8.8)
project(photobooth)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Widgets finds its own dependencies.
find_package(Qt5Widgets REQUIRED)

# Find chdkptp library
find_library(CHDKPTP_LIBRARY NAMES chdkptp
    HINTS
    /home/aspotashev/work/rt00049-canon-a1400/chdkptp
    /home/aspotashev/chdkptp
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(Lua52 REQUIRED)

include_directories(/home/aspotashev/lua-intf)
include_directories(/usr/include/lua5.2)

aux_source_directory(${CMAKE_SOURCE_DIR} photobooth_SRCS)

qt5_wrap_ui(photobooth_UI_SRCS
    mainwindow.ui
    parameterslider.ui
)

qt5_add_resources(photobooth_QRC_SRCS photobooth.qrc)

add_executable(photobooth
    ${photobooth_SRCS}
    ${photobooth_UI_SRCS}
    ${photobooth_QRC_SRCS}
)

target_link_libraries(photobooth
    ${CHDKPTP_LIBRARY}
    ${LUA_LIBRARIES}
)

qt5_use_modules(photobooth Widgets)
