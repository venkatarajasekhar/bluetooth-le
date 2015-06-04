#ifndef btle_corebluetoothperipheraldevice_h
#define btle_corebluetoothperipheraldevice_h

#include "btle/device.h"

#ifdef DESKTOP_BUILD
#import <IOBluetooth/IOBluetooth.h>
#else
#import <CoreBluetooth/CoreBluetooth.h>
#endif

#include <pthread.h>

namespace btle {
    namespace central {
        namespace apple {
            class corebluetoothperipheraldevice: public device
            {
            public:
                corebluetoothperipheraldevice(const bda& addr);
                ~corebluetoothperipheraldevice();

            public:
                void process_adv_data();
                void process_services_discovered(CBPeripheral* peripheral, btle::service_list& list);
                btle::service* process_characteristics_discovered(CBService* service);

                void fetch_service_and_characteristic(CBCharacteristic* aChr,btle::service*& service, btle::characteristic*& chr);
                void fetch_service_and_characteristic(CBDescriptor* aDesc,btle::service*& service, btle::characteristic*& chr);
            
                CBService* fetch_service(const btle::service& srv);
                CBCharacteristic* fetch_characteristic(const btle::characteristic& srv);
                
                CBCharacteristic* fetch_characteristic(const btle::uuid& uid);

            public: // data
                CBPeripheral *peripheral_;

            };
        }
    }
}

#endif
