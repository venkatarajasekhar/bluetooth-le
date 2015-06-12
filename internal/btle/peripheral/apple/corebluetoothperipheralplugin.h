#ifndef COREBLUETOOTHPERIPHERALPLUGIN_H
#define COREBLUETOOTHPERIPHERALPLUGIN_H

#include "peripheral/peripheralplugininterface.h"
#include "btle/peripheral/apple/corebluetoothcentraldevice.h"

#ifdef DESKTOP_BUILD
#import <IOBluetooth/IOBluetooth.h>
#else
#import <CoreBluetooth/CoreBluetooth.h>
#endif

@interface corebluetoothperipheralpluginprivate : NSObject<CBPeripheralManagerDelegate>
{
@public
    void* parent_;
    CBPeripheralManager* manager_;
}
@end

namespace btle {
    namespace peripheral {
        namespace apple {
            class corebluetoothperipheralplugin: public peripheralplugininterface{
            public:

                corebluetoothperipheralplugin(peripheralpluginobserver& observer);

            public:

                unsigned int features();
                const std::string& name();
                void start();
                void stop();
                peripheralplugininterface& operator << (const service& srv);
                void start_advertising(int ms,const adv_fields& fields);
                void stop_advertising();
                std::vector<advertisement_data_type> supported_adtypes();
                std::string read_characteristic(device& central, characteristic& chr);
                void characteristic_written(device& central, characteristic& chr);
                std::string read_descriptor(device& central, characteristic& chr, descriptor& desc);
                std::string descriptor_written(device& central, characteristic& chr, descriptor& desc);
                void characteristic_notify_changed(device& central, characteristic& srv, bool notify);

            public:

                corebluetoothperipheralpluginprivate* peripheral_;
                corebluetoothcentraldevice* central_;
            };
        }
    }
}

#endif // COREBLUETOOTHPERIPHERALPLUGIN_H

