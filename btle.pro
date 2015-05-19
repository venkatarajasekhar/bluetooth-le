
QT       -= gui

TARGET = btle
TEMPLATE = lib

DEFINES += BTLE_LIBRARY BTLE_EXPORT_IMPORT BTLE_EXPORTS DESKTOP_BUILD
INCLUDEPATH += inc inc/btle internal internal/btle internal/btle/central

QMAKE_LIBDIR += "$$DESTDIR"

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
    src/btle/exceptions/link_not_active.cpp \
    src/btle/exceptions/attribute_not_notifyable.cpp \
    src/btle/rssifilter.cpp \
    src/btle/version.cpp \
    src/btle/error.cpp \
    src/btle/exceptions/service_not_found.cpp \
    src/btle/exceptions/not_implemented.cpp \
    src/btle/gatt_services/cyclingpowerservice.cpp \
    src/btle/log.cpp \
    src/btle/utility.cpp \
    src/btle/connectionparameters.cpp \
    src/btle/gatt_services/glucoseservice.cpp \
    src/btle/scanfilterbase.cpp \
    src/btle/uuidscanfilter.cpp \
    src/btle/bdascanfilter.cpp \
    src/btle/central/centralplugininterface.cpp \
    src/btle/rssiscanfilter.cpp \
    src/btle/advertisementfields.cpp \
    src/btle/central/collectorqt.cpp \
    src/btle/central/collectorsimpleqt.cpp \
    src/btle/gatt_services/btlelibservice.cpp \
    src/btle/smpkeys.cpp \
    src/btle/btlelibscanfilter.cpp \
    src/btle/peripheral/peripheralplugininterface.cpp \
    src/btle/peripheral/peripheralpluginfactory.cpp \
    src/btle/peripheral/peripheral.cpp

HEADERS += \
    inc/btle/btle.h\
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
    inc/btle/list_ext.hpp \
    inc/btle/exceptions/attribute_not_notifyable.h \
    inc/btle/rssifilter.h \
    inc/btle/version.h \
    internal/btle/central/connectionhandlerobserver.h \
    inc/btle/error.h \
    inc/btle/exceptions/service_not_found.h \
    inc/btle/exceptions/not_implemented.h \
    inc/btle/gatt_services/cyclingpowerservice.h \
    inc/btle/verify.h \
    internal/btle/central/centralpluginobserver.h \
    inc/btle/log.h \
    inc/btle/utility.h \
    internal/btle/central/centralpluginregisterer.h \
    internal/btle/central/centralpluginregisterer.hpp \
    inc/btle/connectionparameters.h \
    inc/btle/gatt_services/glucoseservice.h \
    inc/btle/scanfilterbase.h \
    inc/btle/uuidscanfilter.h \
    inc/btle/bdascanfilter.h \
    inc/btle/rssiscanfilter.h\
    inc/btle/advertisementfields.h \
    inc/btle/central/collectorqt.h \
    inc/btle/central/collectorsimpleqt.h \
    inc/btle/gatt_services/btlelibservice.h \
    inc/btle/smpkeys.h \
    internal/btle/timer.h \
    internal/btle/timercallback.h \
    internal/btle/central/connectionhandlerlinkctrl.h \
    internal/btle/central/connectionhandlerscanctrl.h \
    inc/btle/btlelibscanfilter.h \
    internal/btle/peripheral/peripheralplugininterface.h \
    inc/btle/gatt_services/gattservicetx.h \
    internal/btle/peripheral/peripheralpluginregisterer.h \
    internal/btle/peripheral/peripheralpluginregisterer.hpp \
    internal/btle/peripheral/peripheralpluginfactory.h \
    internal/btle/peripheral/peripheralpluginobserver.h \
    inc/btle/peripheral/peripheral.h


ios{
    LIBS += -framework Foundation \
            -framework CoreFoundation \
            -framework CoreBluetooth

    OBJECTIVE_HEADERS += internal/btle/central/apple/corebluetoothcentralplugin.h \
                         internal/btle/central/apple/corebluetoothperipheraldevice.h
    OBJECTIVE_SOURCES += src/btle/central/apple/corebluetoothcentralplugin.mm \
                         src/btle/central/apple/corebluetoothperipheraldevice.mm \
                         src/btle/timer_darwin.mm
}

macx{
    LIBS += -framework Foundation \
            -framework CoreFoundation \
            -framework IOBluetooth

    OBJECTIVE_HEADERS += internal/btle/central/apple/corebluetoothcentralplugin.h \
                         internal/btle/central/apple/corebluetoothperipheraldevice.h
    OBJECTIVE_SOURCES += src/btle/central/apple/corebluetoothcentralplugin.mm \
                         src/btle/central/apple/corebluetoothperipheraldevice.mm \
                         src/btle/timer_darwin.mm
}

android{
}

win{
    SOURCES += \
        src/btle/central/win8/win8centralplugin.cpp \
        src/btle/central/win8/win8peripheraldevice.cpp\
        src/btle/timer_win32.cpp

    HEADERS += \
        internal/btle/central/win8/win8centralplugin.h \
        internal/btle/central/win8/win8peripheraldevice.h \
}

linux{
    SOURCES += \
        src/btle/timer_posix.cpp \
        src/btle/central/linux/bluezcentralplugin.cpp \
        src/btle/central/linux/bluezperipheraldevice.cpp

    HEADERS += \
        internal/btle/central/linux/bluezcentralplugin.h \
        internal/btle/central/linux/bluezperipheraldevice.h
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
