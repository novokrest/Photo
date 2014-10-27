#-------------------------------------------------
#
# Project created by QtCreator 2014-10-16T16:30:59
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=c++11

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PhotoB
TEMPLATE = app

INCLUDEPATH += /usr/include/lua5.2
LIBS += -L"$$_PRO_FILE_PWD_/" -lchdkptp
LIBS += -llua5.2

SOURCES += main.cpp\
    camera.cpp \
    chdkptpmanager.cpp \
    parameterslider.cpp \
    mainwindow.cpp \
    propertyresolver.cpp \
    utils.cpp

HEADERS  += mainwindow.h \
    camera.h \
    chdkptpmanager.h \
    luaapi.h \
    parameterslider.h \
    ui_mainwindow.h \
    ui_parameterslider.h \
    utils.h \
    propertyresolver.h \
    commands.h \
    properties.h

FORMS    += \
    mainwindow.ui \
    parameterslider.ui

OTHER_FILES +=

RESOURCES += \
    photobooth.qrc
