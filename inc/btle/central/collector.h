#ifndef COLLECTOR_H
#define COLLECTOR_H

#include "btle/uuid.h"
#include "btle/device.h"
#include "btle/bda.h"

namespace btle {
    namespace central {
        /**
         * @brief The collector class, main interface class for lib central usage
         */
        class collector{
        public:

            collector();

        public:

            void set_scan_filter(const std::vector<uuid>& filter);
            void set_scan_filter(const uuid& uid);
            void start_scan();
            void stop_scan();

        public: // device connection/disconnection

            void auto_connect(const bda& addr);
            void connect_device(device& dev);
            void disconnect_device(device& dev);
            void disconnect_device(const bda& addr);

        public: // device gatt operations

            void read_characteristic_value(device& dev, const uuid& uid);
            void read_characteristic_value(device& dev, const uuid_pair& pair);
            void write_characteristic_value(device& dev, const uuid& uid);
            void write_characteristic_value(device& dev, const uuid_pair& pair);
            void set_characteristic_notify(device& dev, const uuid& uid, bool notify);
            void set_characteristic_notify(device& dev, const uuid_pair& pair, bool notify);

        private:

            std::vector<uuid> filter_;
        };
    }
}

#endif // COLLECTOR_H

