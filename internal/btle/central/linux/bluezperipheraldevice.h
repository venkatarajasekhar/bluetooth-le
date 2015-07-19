#ifndef BLUEZPERIPHERALDEVICE_H
#define BLUEZPERIPHERALDEVICE_H

#include "btle/device.h"

namespace btle {
    namespace central {
        namespace linux_platform {
            class bluezperipheraldevice: public device
            {
            public:
                bluezperipheraldevice(const btle::bda& addr);
            };
        }
    }
}

#endif // BLUEZPERIPHERALDEVICE_H

