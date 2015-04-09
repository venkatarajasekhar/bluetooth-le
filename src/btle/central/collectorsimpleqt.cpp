
#include "btle/central/collectorsimpleqt.h"

using namespace btle::central;

collectorsimpleqt::collectorsimpleqt(QObject* parent)
: QObject(parent)
{
}

collectorsimpleqt::~collectorsimpleqt()
{
}

void collectorsimpleqt::connect_device(const QString &addr)
{
    collector::connect_device(btle::bda(addr.toStdString()));
}

void collectorsimpleqt::disconnect_device(const QString &addr)
{
    collector::disconnect_device(btle::bda(addr.toStdString()));
}

void collectorsimpleqt::device_discovered_cb(device& dev)
{
    emit signal_device_discovered(QString::fromStdString(dev.addr().to_string()),
                                  QString::fromStdString(dev.name()));
}

void collectorsimpleqt::device_service_value_updated_cb(device& dev, const gatt_services::gattservicebase* srv)
{
}

void collectorsimpleqt::device_service_value_updated_cb(device& dev, const service& srv, const characteristic& chr, const std::string& data)
{
}

void collectorsimpleqt::device_gatt_service_discovered_cb(device& dev, const gatt_services::gattservicebase *srv)
{
}

void collectorsimpleqt::device_service_discovery_failed_cb(device& dev, const service_list& services, const error& err)
{
}

void collectorsimpleqt::device_characteristic_discovery_failed_cb(device& dev, const service& srv, const chr_list& chrs, const error& err)
{
}

void collectorsimpleqt::device_characteristic_read_cb(device& dev, const service& srv, const characteristic& chrs, const std::string& data, const error& err)
{
    emit signal_device_characteristic_read(QString::fromStdString(dev.addr().to_string()),
                                           QString::fromStdString(dev.name()),
                                           QString::fromStdString(srv.to_string()),
                                           QString::fromStdString(chrs.to_string()),
                                           QString::fromStdString(data),
                                           err.code());
}

void collectorsimpleqt::device_state_changed_cb(device& dev)
{
    emit signal_device_state_changed(QString::fromStdString(dev.addr().to_string()),
                                     QString::fromStdString(dev.state_string()));
}


