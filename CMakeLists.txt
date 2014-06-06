project(photobooth)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(photobooth_SRCS photobooth.cpp main.cpp)
qt4_automoc(${photobooth_SRCS})
add_executable(photobooth ${photobooth_SRCS})
target_link_libraries(photobooth ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
install(TARGETS photobooth RUNTIME DESTINATION bin)
