#-------------------------------------------------
#
# Project created by QtCreator 2015-02-08T00:14:41
#
#-------------------------------------------------

QT       -= gui

TARGET = btle
TEMPLATE = lib

DEFINES += BTLE_LIBRARY
INCLUDEPATH += inc inc/btle internal internal/btle internal/btle/central

SOURCES += \
    src/btle/base.cpp \
    src/btle/uuid.cpp \
    src/btle/characteristic.cpp \
    src/btle/descriptor.cpp \
    src/btle/bda.cpp \
    src/btle/advertisementdata.cpp \
    src/btle/device.cpp \
    src/btle/gatt_services/gattservicebase.cpp \
    src/btle/gatt_services/hrservice.cpp \
    src/btle/gatt_services/gattservicefactory.cpp \
    src/btle/gattdatabase.cpp \
    src/btle/service.cpp \
    src/btle/central/connectionhandler.cpp \
    src/btle/gatt_services/rscservice.cpp \
    src/btle/gatt_services/cscservice.cpp \
    src/btle/central/centralpluginfactory.cpp \
    src/btle/central/collector.cpp \
    src/btle/exceptions/attribute_not_found.cpp \
    src/btle/exceptions/attribute_not_readable.cpp \
    src/btle/exceptions/attribute_not_writable.cpp \
    src/btle/exceptions/device_not_connected.cpp \
    src/btle/exceptions/link_not_active.cpp

HEADERS += inc/btle/btle.h\
        inc/btle/btle_global.h \
    inc/btle/base.h \
    inc/btle/uuid.h \
    inc/btle/characteristic.h \
    inc/btle/descriptor.h \
    inc/btle/bda.h \
    inc/btle/advertisementdata.h \
    inc/btle/device.h \
    inc/btle/gatt_services/gattservicebase.h \
    inc/btle/gatt_services/hrservice.h \
    inc/btle/gatt_services/gattservicefactory.h \
    inc/btle/gatt_services/gattserviceregisterer.h \
    inc/btle/gatt_services/gattserviceregisterer.hpp \
    inc/btle/gattdatabase.h \
    inc/btle/service.h \
    internal/btle/central/connectionhandler.h \
    internal/btle/central/centralplugininterface.h \
    inc/btle/gatt_services/rscservice.h \
    inc/btle/gatt_services/cscservice.h \
    inc/btle/central/collector.h \
    internal/btle/central/centralpluginfactory.h \
    inc/btle/exceptions/attribute_not_found.h \
    inc/btle/exceptions/attribute_not_readable.h \
    inc/btle/exceptions/attribute_not_writable.h \
    inc/btle/exceptions/device_not_connected.h \
    inc/btle/exceptions/link_not_active.h \
    inc/btle/list_ext.h \
    inc/btle/list_ext.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
