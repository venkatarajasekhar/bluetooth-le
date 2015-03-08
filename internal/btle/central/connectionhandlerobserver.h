#ifndef CONNECTIONHANDLEROBSERVER_H
#define CONNECTIONHANDLEROBSERVER_H

#include "btle/device.h"

namespace btle {
    namespace central {
        class connectionhandlerobserver{
        public:

            virtual void scan_devices()=0;
            virtual void stop_device_scan()=0;
            virtual void device_state_updated(device& dev)=0;

        };
    }
}


#endif // CONNECTIONHANDLEROBSERVER_H

