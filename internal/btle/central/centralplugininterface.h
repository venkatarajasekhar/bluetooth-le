#ifndef CENTRALPLUGININTERFACE_H
#define CENTRALPLUGININTERFACE_H

#include "btle/device.h"

namespace btle {
    namespace central {
        class centralplugininterface{
        public:

            virtual int start() = 0;
            virtual void stop() = 0;
            virtual void start_scan() = 0;
            virtual void stop_scan() = 0;

            virtual void connect_device(device& dev)=0;
            virtual void disconnect_device(device& dev)=0;
            virtual void cancel_pending_connection(device& dev)=0;
        };
    }
}

#endif // CENTRALPLUGININTERFACE_H

