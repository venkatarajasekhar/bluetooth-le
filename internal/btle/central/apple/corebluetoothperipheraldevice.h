#ifndef btle_corebluetoothperipheraldevice_h
#define btle_corebluetoothperipheraldevice_h

#include "btle/device.h"

#ifdef DESKTOP_BUILD
#import <IOBluetooth/IOBluetooth.h>
#else
#import <CoreBluetooth/CoreBluetooth.h>
#endif

namespace btle {
    namespace central {
        namespace apple {
            class corebluetoothperipheraldevice: public device
            {
            public:
                corebluetoothperipheraldevice(const bda& addr);
                void process_adv_data();
            };
        }
    }
}

#endif
