
#ifndef btle_corebluetoothcentraldevice_h
#define btle_corebluetoothcentraldevice_h

#include "btle/device.h"

#ifdef DESKTOP_BUILD
#import <IOBluetooth/IOBluetooth.h>
#else
#import <CoreBluetooth/CoreBluetooth.h>
#endif

namespace btle {
    namespace peripheral{
        namespace apple{
            class corebluetoothcentraldevice: public device{
            public:
                corebluetoothcentraldevice(CBCentral* central);
                CBCentral* central();
                
            private:
                CBCentral* central_;
            };
        }
    }
}

#endif
