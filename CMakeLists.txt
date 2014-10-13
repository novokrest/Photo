cmake_minimum_required(VERSION 2.8.8)
project(photobooth)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -ggdb")

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}/build)
set(LIBS_PATH ${CMAKE_SOURCE_DIR}/libs)

# Widgets finds its own dependencies.
find_package(Qt5Widgets REQUIRED)

# Find chdkptp library
find_library(CHDKPTP_LIBRARY NAMES chdkptp
    HINTS
    ${LIBS_PATH}/chdkptp
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(Lua52 REQUIRED)

include_directories(${LIBS_PATH}/lua-intf)
include_directories(/usr/include/lua5.2)
include_directories(${CMAKE_SOURCE_DIR}/headers)

aux_source_directory(${CMAKE_SOURCE_DIR}/src photobooth_SRCS)

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

qt5_wrap_ui(photobooth_UI_SRCS
    ${CMAKE_SOURCE_DIR}/src/ui/mainwindow.ui
    ${CMAKE_SOURCE_DIR}/src/ui/parameterslider.ui
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

