#ifndef CENTRALPLUGINOBSERVER_H
#define CENTRALPLUGINOBSERVER_H

#include "btle/device.h"
#include "btle/error.h"

namespace btle {
    namespace central {
        class centralpluginobserver{
        public:
            virtual void plugin_state_changed(central_plugin_state state)=0;
            virtual void device_discovered(device& dev) = 0;
            virtual void device_connected(device& dev)=0;
            virtual void device_disconnected(device& dev)=0;
            virtual void device_services_discovered(device& dev, const service_list& services, const error& err) = 0;
            virtual void device_characteristics_discovered(device& dev, const service& srv, const chr_list& chrs, const error& err) = 0;
            virtual void device_characteristic_read(device& dev, const service& srv, const characteristic& chr, const std::string& data, const error& err) = 0;
            virtual void device_characteristic_written(device& dev, const service& srv, const characteristic& chr, const error& err) = 0;
            virtual void device_characteristic_nofication_state_changed(device& dev, const service& srv, const characteristic& chr, bool notify, const error& err) = 0;
            virtual void device_characteristic_notify_data_updated(device& dev, const service& srv, const characteristic& chr, const std::string& data) = 0;

        };
    }
}

#endif // CENTRALPLUGINOBSERVER_H

