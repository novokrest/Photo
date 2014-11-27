QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    devicemanager.cpp \
    stuff.cpp \
    chdkptp_sources.cpp

INCLUDEPATH += \
    chdkptp \
    chdkptp/chdk_headers/


LIBS += -L"$$_PRO_FILE_PWD_/" -lchdkptp -lusb

HEADERS += \
    devicemanager.h \
    chdkptp/ptp.h \
    chdkptp/ptpcam.h \
    chdkptp/chdk_headers/core/ptp.h \
    chdhkptp_header.h

OTHER_FILES += \
    CameraCommunication \
    libchdkptp.so \
    main.o \
    CameraCommunication.pro.user \
    Makefile

