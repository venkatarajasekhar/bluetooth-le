
QT       += core

QT       -= gui

TARGET = btleqttest
CONFIG   += console
CONFIG   -= app_bundle

DEFINES += BTLE_LIBRARY BTLE_EXPORT_IMPORT

INCLUDEPATH += ../bluetoothle/inc ../bluetoothle/inc/btle ../bluetoothle/internal ../bluetoothle/internal/btle

TEMPLATE = app

QMAKE_LIBDIR += "$$DESTDIR"

win{

}
macx{
    LIBS += "$$DESTDIR"/libbluetoothle.1.0.0.dylib
}

QMAKE_LIBDIR += "$$DESTDIR"

SOURCES += main.cpp \
    collectortest.cpp

HEADERS += \
    collectortest.h
