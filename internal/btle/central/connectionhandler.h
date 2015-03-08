#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include "btle/central/connectionhandlerobserver.h"
#include "btle/central/centralplugininterface.h"
#include "btle/device.h"
#include <vector>

namespace btle {
    namespace central {
        class connectionhandler;
        /**
         * function pointer declaration
         */
        typedef void (connectionhandler::*kConnectionHndlrState)( device&, int );


        class connectionhandler{
        public:
            connectionhandler();

            // when new adv has been received
            void advertisement_head_received(device &dev);

            // client/user action
            void connect_device(device &dev );
            void disconnect_device( device& dev );

            // callbacks when device has been really connected or disconnected
            void device_connected(device &dev );
            void device_disconnected( device& dev );

        protected:

            void change_device_state( device& dev, btle::connection_state state );

        private: // states

            void free( device& dev, int action );
            void connecting( device& dev, int action );
            void disconnecting( device& dev, int action );
            void change_state(kConnectionHndlrState state, device &dev);

        private: //

        private: // private functions

            bool is_reconnection_needed(device& dev);

        private: // data

            kConnectionHndlrState current_;
            kConnectionHndlrState free_;
            kConnectionHndlrState connecting_;
            kConnectionHndlrState disconnecting_;
            device* current_device_;
            connectionhandlerobserver* observer_;
            centralplugininterface* central_;
            int reconnectiontryes_;
        };
    }
}

#endif // CONNECTIONHANDLER_H

