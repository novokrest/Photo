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

INCLUDEPATH += /usr/include/lua5.2 \
    communication/chdkptp \
    communication/chdkptp/chdk_headers/

LIBS += -L"$$_PRO_FILE_PWD_/" -lchdkptp -lusb
LIBS += -llua5.2
#LIBS += -L/home/knovokreshchenov/ -lchdkptp

SOURCES += main.cpp\
    camera.cpp \
    chdkptpmanager.cpp \
    parameterslider.cpp \
    mainwindow.cpp \
    propertyresolver.cpp \
    utils.cpp \
    commandmanager.cpp \
    communication/devicemanager.cpp \
    communication/scriptloader.cpp \
    communication/stuff.cpp \
    communication/test.cpp

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
    properties.h \
    commandmanager.h \
    communication/chdhkptp_header.h \
    communication/devicemanager.h \
    communication/scriptloader.h \
    communication/chdkptp/ptp.h \
    communication/chdkptp/chdk_headers/core/ptp.h \
    communication/chdkptp/ptpcam.h

FORMS    += \
    mainwindow.ui \
    parameterslider.ui \
    testedwindow.ui

OTHER_FILES += \
    canonPS_SX150_IS.txt \
    communication/commands/download.script \
    communication/commands/listdir.script \
    communication/commands/multicam_start.script \
    communication/commands/play.script \
    communication/commands/rec.script \
    communication/commands/shoot.script

RESOURCES += \
    photobooth.qrc
