#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include "btle/central/connectionhandlerobserver.h"
#include "btle/central/centralplugininterface.h"
#include "btle/device.h"

#include <vector>
#include <map>

namespace btle {
    namespace central {

        enum connectionhandler_options{
            /**
             * default connection handler behaviour, and recommemded one,
             * trigger connection from advertisement head
             */
            CONNECTION_FROM_ADVERTISEMENT_HEAD = 0,
            /**
             * connection is direct ie will suspend connection handler
             * if no timeout has been set
             */
            CONNECTION_DIRECT                  = 0x01,
            CONNECTION_TIMEOUT                 = 0x02,
            DISCONNECTION_TIMEOUT              = 0x04,
            RECONNECTION_TRYES                 = 0x08
        };

        class connectionhandler;

        /**
         * function pointer declaration
         */
        typedef void (connectionhandler::*kConnectionHndlrState)( device&, int );


        class BTLE_API connectionhandler
        {
        public:
            connectionhandler();

        private:

            // when new adv has been received
            void advertisement_head_received(device &dev);

            // client/user action
            void connect_device(device &dev );
            void disconnect_device( device& dev );

            // callbacks when device has been really connected or disconnected
            void device_connected(device &dev );
            void device_disconnected( device& dev );

        public:

            void set_option(connectionhandler_options option, int value = 0);
            void remove_option(connectionhandler_options option);
            void attach(connectionhandlerobserver* observer);
            void detach(connectionhandlerobserver* observer);

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
            centralplugininterface* central_;
            int reconnectiontryes_;
            std::map<connectionhandler_options,int> options_;
            std::vector<connectionhandlerobserver*> observers_;

            friend class collector;
        };
    }
}

#endif // CONNECTIONHANDLER_H

