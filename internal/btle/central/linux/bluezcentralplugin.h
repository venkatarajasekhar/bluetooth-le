#ifndef BLUEZCENTRALPLUGIN_H
#define BLUEZCENTRALPLUGIN_H

#include "btle/central/centralplugininterface.h"

#include <bluetooth/bluetooth.h>

namespace btle {
    namespace central {
        namespace linux_platform {
            class bluezcentralplugin: public centralplugininterface, public base{
            public:
                bluezcentralplugin(centralpluginobserver& observer);

            public: // from base

                const std::string& name();
                std::vector<device*>& devices();
                device* allocate_new_device(const bda& addr);
                int start();
                void stop();
                void start_scan( central_scan_parameters param = SCAN_HIGH_DUTY, const uuid_list* services = NULL );
                void stop_scan();
                void connect_device(device& dev);
                void disconnect_device(device& dev);
                void cancel_pending_connection(device& dev);
                void discover_services(device& dev);
                void discover_characteristics(device& dev, const service& srv);
                void read_characteristic_value(device& dev,const service& srv, const characteristic& chr);
                void write_characteristic_value(device& dev,const service& srv, const characteristic& chr, const std::string& data, characteristic_properties type);
                void set_characteristic_notify(device& dev,const service& srv, const characteristic& chr, bool notify);
                void write_descriptor(device& dev, const service& srv, const characteristic& chr, descriptor& desc, bool notify);

            private:

                int id_;
                int handle_;
            };
        }
    }
}

#endif // BLUEZCENTRALPLUGIN_H

