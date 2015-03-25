#ifndef CONNECTIONHANDLEROBSERVER_H
#define CONNECTIONHANDLEROBSERVER_H

#include "btle/device.h"

namespace btle {
    class connectionhandlerobserver{
    public:
        virtual void device_state_changed(btle::device& dev) = 0;
    };
}

#endif // CONNECTIONHANDLEROBSERVER_H

