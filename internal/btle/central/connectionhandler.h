#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

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

        private: // states

            void free( device& dev, int action );
            void connecting( device& dev, int action );
            void disconnecting( device& dev, int action );
            void change_state(kConnectionHndlrState state, device &dev);

        private: //

        private: // private functions

        private: // data

            kConnectionHndlrState current_state_;
            kConnectionHndlrState free_state_;
            kConnectionHndlrState connecting_state_;
            kConnectionHndlrState disconnecting_state_;
            device* current_device_;
        };
    }
}

#endif // CONNECTIONHANDLER_H

