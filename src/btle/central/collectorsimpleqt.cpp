
#include "btle/central/collectorsimpleqt.h"
#include "btle/gatt_services/hrservice.h"
#include "btle/gatt_services/rscservice.h"
#include "btle/gatt_services/cscservice.h"

using namespace btle::central;
using namespace btle::gatt_services;

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
    emit signal_device_service_value_updated(QString::fromStdString(dev.addr().to_string()),
                                             QString::fromStdString(dev.name()),
                                             QString::fromStdString(srv->service_uuid().to_string()),
                                             "");
    switch( srv->service_uuid().uuid16bit() )
    {
        case HEART_RATE_SERVICE:
        {
            const hrservice* hr = (const hrservice*)srv;
            QList<int> rrs;
            for( std::vector<int>::const_iterator it = hr->rr_values().begin(); it != hr->rr_values().end(); ++it)
            {
                rrs.append(*it);
            }
            emit signal_device_hr_value_updated(QString::fromStdString(dev.addr().to_string()),
                                                QString::fromStdString(dev.name()),
                                                hr->hr_value(),
                                                rrs,
                                                hr->sensor_contact(),
                                                hr->energy_expeneded());
            break;
        }
        case RSC_SERVICE:
        {
            const rscservice* rsc = (const rscservice*)srv;
            emit signal_device_rsc_value_updated(QString::fromStdString(dev.addr().to_string()),
                                                 QString::fromStdString(dev.name()),
                                                 rsc->speed(),
                                                 rsc->is_walking(),
                                                 rsc->cadence(),
                                                 rsc->stride_length(),
                                                 rsc->distance());
            break;
        }
        case CSC_SERVICE:
        {
            const cscservice* csc = (const cscservice*)srv;
            emit signal_device_csc_value_updated(QString::fromStdString(dev.addr().to_string()),
                                                 QString::fromStdString(dev.name()),
                                                 csc->speed(),
                                                 csc->cadence(),
                                                 csc->is_speed_present(),
                                                 csc->is_cadence_present());
            break;
        }
    }
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


