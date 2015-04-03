#ifndef COLLECTOR_H
#define COLLECTOR_H

#include "btle/uuid.h"
#include "btle/device.h"
#include "btle/bda.h"
#include "btle/scanfilterbase.h"
#include "btle/central/centralplugininterface.h"
#include "btle/central/centralpluginobserver.h"
#include "btle/central/connectionhandler.h"

namespace btle {
    namespace central {
        /**
         * @brief The collector class, main interface class for lib central usage
         */
        class BTLE_API collector: public centralpluginobserver{
        public:

            collector();
            ~collector();

        public: // plugin start/stop etc...
            
            int auto_start();
            
        public: // scannning

            void add_scan_filter(scanfilterbase* filter);
            void clear_scan_filter(scanfilterbase* filter);
            void clear_scan_filters();

            void start_scan();
            void stop_scan();

        public: // settings related apis

            connectionhandler& connection_handler();

        public:

            void set_auto_read_values(const uuid_list& list);
            void set_auto_notify_values(const uuid_list& list);

        public: // device connection/disconnection

            void connect_device(const bda& addr);
            void connect_device(device& dev);
            void disconnect_device(device& dev);
            void disconnect_device(const bda& addr);

        public: // device gatt operations

            void read_characteristic_value(device& dev, const uuid& uid);
            void read_characteristic_value(device& dev, const uuid_pair& pair);
            void write_characteristic_value(device& dev, const uuid& uid, const std::string &data, bool write_with_out_resp = false);
            void write_characteristic_value(device& dev, const uuid_pair& pair, const std::string& data, bool write_with_out_resp = false);
            void set_characteristic_notify(device& dev, const uuid& uid, bool notify);
            void set_characteristic_notify(device& dev, const uuid_pair& pair, bool notify);

        private: // from observer

            void plugin_state_changed(central_plugin_state state);
            void device_discovered(device& dev);
            void device_services_discovered(device& dev, const service_list& services, const error& err);
            void device_characteristics_discovered(device& dev, const service& srv, const chr_list& chrs, const error& err);
            void device_characteristic_read(device& dev, const service& srv, const characteristic& chr, const std::string& data, const error& err);
            void device_characteristic_written(device& dev, const service& srv, const characteristic& chr, const error& err);
            void device_characteristic_nofication_state_changed(device& dev, const service& srv, const characteristic& chr, bool notify, const error& err);
            void device_characteristic_notify_data_updated(device& dev, const service& srv, const characteristic& chr, const std::string &data);

        public: // callbacks

            /**
             * @brief device_discovered_cb, whenever a device has been discovered during scanning
             * @param dev
             */
            virtual void device_discovered_cb(device& dev) = 0;

            /**
             * @brief device_service_value_updated_cb, called upon whenever gatt service has been updated
             * e.g. famous heart rate example:
             *
             *      switch( srv->service_uuid().uuid16bit() )
             *      {
             *          case HEART_RATE_SERVICE:
             *          {
             *              const hrservice* hr = ((const hrservice*)srv);
             *              printf("Heart rate is: %d", hr->hr_value());
             *              break;
             *          }
             *          etc...
             *      }
             *
             * @param dev
             * @param srv
             */
            virtual void device_service_value_updated_cb(device& dev, const gatt_services::gattservicebase* srv) = 0;

            /**
             * @brief device_service_value_updated_cb
             * @param dev
             * @param srv
             * @param chr
             * @param data
             */
            virtual void device_service_value_updated_cb(device& dev, const service& srv, const characteristic& chr, const std::string& data) = 0;

            virtual void device_gatt_service_discovered_cb(device& dev, const gatt_services::gattservicebase *srv);
            virtual void device_service_discovery_failed_cb(device& dev, const service_list& services, const error& err);
            virtual void device_characteristic_discovery_failed_cb(device& dev, const service& srv, const chr_list& chrs, const error& err);

        private:

            device* fetch_device(const bda& addr);

        private:

            uuid_list notify_uuids_;
            uuid_list read_uuids_;
            centralplugininterface* plugin_;
            std::vector<centralplugininterface*> plugins_;
            connectionhandler connectionhandler_;
            unsigned int flags_;
            scan_filters filters_;
            central_plugin_state state_;
        };
    }
}

#endif // COLLECTOR_H

