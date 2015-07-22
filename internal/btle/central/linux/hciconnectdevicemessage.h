#ifndef HCICONNECTDEVICEMESSAGE
#define HCICONNECTDEVICEMESSAGE

#include "btle/central/linux/messagebase.h"

namespace btle {
    namespace central {
        class centralpluginobserver;
        namespace linux_platform {
            class bluezperipheraldevice;
            class hciconnectdevicemessage: public messagebase{
            public:

                hciconnectdevicemessage(int handle,centralpluginobserver* observer);

            public:

                void process(bluezperipheraldevice* dev);

            private: //data

                int handle_;
                centralpluginobserver* observer_;
            };
        }
    }
}

#endif // HCICONNECTDEVICEMESSAGE

