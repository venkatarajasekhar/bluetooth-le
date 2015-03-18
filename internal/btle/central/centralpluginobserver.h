#ifndef CENTRALPLUGINOBSERVER_H
#define CENTRALPLUGINOBSERVER_H

#include "btle/device.h"
#include "btle/error.h"

namespace btle {
    namespace central {
        class centralpluginobserver{
        public:
            virtual void device_discovered(device& dev) = 0;
            virtual void device_services_discovered(device& dev, const service_list& services, const error& err) = 0;
            virtual void device_characteristics_discovered(device& dev, const service& srv, const chr_list& chrs, const error& err) = 0;
            virtual void device_characteristic_read(device& dev, const uuid_pair& pair, const std::string& data, const error& err) = 0;
            virtual void device_characteristic_written(device& dev, const uuid_pair& pair, const error& err) = 0;
            virtual void device_characteristic_nofication_state_changed(device& dev, const uuid_pair& pair, bool notify, const error& err) = 0;
            virtual void device_characteristic_notify_data_updated(device& dev, const uuid_pair& pair, bool notify, const error& err) = 0;

        };
    }
}

#endif // CENTRALPLUGINOBSERVER_H

