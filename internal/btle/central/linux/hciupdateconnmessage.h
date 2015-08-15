#ifndef HCIUPDATECONNMESSAGE_H
#define HCIUPDATECONNMESSAGE_H

#include "btle/central/linux/messagebase.h"
#include "btle/connectionparameters.h"

namespace btle {
    namespace central {
        class centralpluginobserver;
        namespace linux_platform {
            class bluezperipheraldevice;
            class hciupdateconnmessage: public messagebase{
            public:

                hciupdateconnmessage(int handle, centralpluginobserver* observer, const connectionparameters& parameters);

            public:

                void process(bluezperipheraldevice* dev);

            private: //data

                int handle_;
                centralpluginobserver* observer_;
                connectionparameters parameters_;
            };
        }
    }
}

#endif // HCIUPDATECONNMESSAGE_H

