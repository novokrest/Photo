#-------------------------------------------------
#
# Project created by QtCreator 2014-10-23T14:47:25
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=c++11

QT       += core

QT       -= gui

TARGET = Console_PhotoB
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../PhotoB/

INCLUDEPATH += /usr/include/lua5.2
LIBS += -L"$$_PRO_FILE_PWD_/../PhotoB" -lchdkptp
LIBS += -llua5.2

SOURCES += main.cpp \
    ../PhotoB/chdkptpmanager.cpp \
    ../PhotoB/camera.cpp

HEADERS += \
    ../PhotoB/chdkptpmanager.h \
    ../PhotoB/camera.h \
    ../PhotoB/utils.h
