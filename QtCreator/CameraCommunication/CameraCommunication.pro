QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    devicemanager.cpp \
    stuff.cpp \
    scriptloader.cpp \
    luatableparser.cpp \
    cameracommunication_utils.cpp

INCLUDEPATH += \
    chdkptp \
    chdkptp/chdk_headers/


LIBS += -L"$$_PRO_FILE_PWD_/" -lchdkptp -lusb

HEADERS += \
    devicemanager.h \
    chdkptp/ptp.h \
    chdkptp/ptpcam.h \
    chdkptp/chdk_headers/core/ptp.h \
    chdhkptp_header.h \
    scriptloader.h \
    luatableparser.h \
    common.h \
    remoteinode.h \
    cameracommunication_utils.h

OTHER_FILES += \
    libchdkptp.so \
    Commands/mc.start_single.script \
    Commands/play.script \
    Commands/rec.script \
    Commands/shoot.script \
    commands/play.script \
    commands/rec.script \
    commands/shoot.script \
    commands/multicam_start.script \
    commands/download.script \
    commands/listdir.script

