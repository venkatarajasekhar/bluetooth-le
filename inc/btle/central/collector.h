#ifndef COLLECTOR_H
#define COLLECTOR_H

#include "btle/uuid.h"
#include "btle/device.h"
#include "btle/bda.h"
#include "btle/central/centralplugininterface.h"
#include "btle/central/connectionhandler.h"

namespace btle {
    namespace central {
        /**
         * @brief The collector class, main interface class for lib central usage
         */
        class collector{
        public:

            collector();

        public:

            void set_scan_filter(const uuid_list& filter);
            void set_scan_filter(const bda_list& bdas);
            void start_scan();
            void stop_scan();

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

        private:

            device* fetch_device(const bda& addr);

        private:

            uuid_list filter_;
            bda_list  bda_filter_;
            uuid_list notify_uuids_;
            uuid_list read_uuids_;
            centralplugininterface* plugin_;
            connectionhandler connectionhandler_;
        };
    }
}

#endif // COLLECTOR_H

