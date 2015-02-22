#-------------------------------------------------
#
# Project created by QtCreator 2015-02-08T00:14:41
#
#-------------------------------------------------

QT       -= gui

TARGET = btle
TEMPLATE = lib

DEFINES += BTLE_LIBRARY
INCLUDEPATH += inc inc/btle

SOURCES += src/btle/btle.cpp \
    src/btle/base.cpp \
    src/btle/uuid.cpp \
    src/btle/characteristic.cpp \
    src/btle/descriptor.cpp \
    src/btle/bda.cpp \
    src/btle/advertisementdata.cpp

HEADERS += inc/btle/btle.h\
        inc/btle/btle_global.h \
    inc/btle/base.h \
    inc/btle/uuid.h \
    inc/btle/characteristic.h \
    inc/btle/descriptor.h \
    inc/btle/bda.h \
    inc/btle/advertisementdata.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
