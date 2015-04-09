#ifndef COLLECTORSIMPLEQT_H
#define COLLECTORSIMPLEQT_H

#include <QObject>

#include "btle/central/collector.h"

namespace btle {
    namespace central {
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

            /**
             * @brief signal_device_discovered
             * @param addr
             * @param name
             */
            void signal_device_discovered(const QString& addr, const QString& name);
            void signal_device_service_value_updated(const QString& addr, const QString& name,const QString& srv,const QString& primary_measurement, double value, const QString& json);
            void signal_device_characteristic_read(const QString& addr, const QString& name,const QString& srv, const QString& chr, const QString& data, int err);
            void signal_device_state_changed(const QString& addr, const QString state);

        private: // data

        };
    }
}


#endif // COLLECTORSIMPLEQT_H

