#ifndef COLLECTORSIMPLEQT_H
#define COLLECTORSIMPLEQT_H

#include <QObject>

#include "btle/central/collector.h"

namespace btle {
    namespace central {
        /**
         * @brief The collectorsimpleqt class
         * super simple ble qt api, but still contains the most important features
         */
        class BTLE_API collectorsimpleqt: public QObject, public collector{
        Q_OBJECT

        public:
            explicit collectorsimpleqt(QObject* parent=NULL);
            ~collectorsimpleqt();

        public: // some extra apis

            void connect_device(const QString& addr);
            void disconnect_device(const QString& addr);

        public:

            void device_discovered_cb(device& dev);
            void device_service_value_updated_cb(device& dev, const gatt_services::gattservicebase* srv);
            void device_service_value_updated_cb(device& dev, const service& srv, const characteristic& chr, const std::string& data);
            void device_gatt_service_discovered_cb(device& dev, const gatt_services::gattservicebase *srv);
            void device_service_discovery_failed_cb(device& dev, const service_list& services, const error& err);
            void device_characteristic_discovery_failed_cb(device& dev, const service& srv, const chr_list& chrs, const error& err);
            void device_characteristic_read_cb(device& dev, const service& srv, const characteristic& chrs, const std::string& data, const error& err);
            void device_state_changed_cb(device& dev);

        signals:

            void signal_device_discovered(const QString& addr, const QString& name);
            void signal_device_service_value_updated(const QString& addr, const QString& name,const QString& srv, const QString& json);
            void signal_device_hr_value_updated(const QString& addr, const QString& name, int hr, const QList<int>& rrs, bool contact, int energy);
            void signal_device_rsc_value_updated(const QString& addr, const QString& name, double speed, bool walking, int cadence, int stride_length, double distance);
            void signal_device_csc_value_updated(const QString& addr, const QString& name, double speed, int cadence, bool speed_present, bool cadence_present);
            void signal_device_characteristic_read(const QString& addr, const QString& name,const QString& srv, const QString& chr, const QString& data, int err);
            void signal_device_state_changed(const QString& addr, const QString& state);

        private: // data

        };
    }
}


#endif // COLLECTORSIMPLEQT_H

