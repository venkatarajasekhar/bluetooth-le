#ifndef CENTRALPLUGINOBSERVER_H
#define CENTRALPLUGINOBSERVER_H

#include "btle/device.h"

namespace btle {
    namespace central {
        class centralpluginobserver{
        public:
            virtual void device_discovered(device& dev) = 0;
        };
    }
}

#endif // CENTRALPLUGINOBSERVER_H

