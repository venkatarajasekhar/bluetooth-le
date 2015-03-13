#ifndef CENTRALPLUGININTERFACE_H
#define CENTRALPLUGININTERFACE_H


#include "btle/device.h"

namespace btle {
    namespace central {
        class centralplugininterface{
        public:

            /**
             * @brief devices
             * @return
             */
            virtual std::vector<device*>& devices() = 0;

            /**
             * @brief allocate_new_device
             * @param addr
             * @return
             */
            virtual device* allocate_new_device(const bda& addr) = 0;

            /**
             * @brief start
             * @return
             */
            virtual int start() = 0;

            /**
             * @brief stop
             */
            virtual void stop() = 0;

            /**
             * @brief start_scan
             */
            virtual void start_scan( const uuid_list* services = NULL ) = 0;

            /**
             * @brief stop_scan
             */
            virtual void stop_scan() = 0;

            /**
             * @brief connect_device
             * @param dev
             */
            virtual void connect_device(device& dev)=0;

            /**
             * @brief disconnect_device
             * @param dev
             */
            virtual void disconnect_device(device& dev)=0;

            /**
             * @brief cancel_pending_connection
             * @param dev
             */
            virtual void cancel_pending_connection(device& dev)=0;

            /**
             * @brief read_characteristic_value
             */
            virtual void read_characteristic_value(device& dev,const service& srv, const characteristic& chr) = 0;

            /**
             * @brief write_characteristic_value
             * @param dev
             * @param srv
             * @param chr
             * @param data
             * @param type
             */
            virtual void write_characteristic_value(device& dev,const service& srv, const characteristic& chr, const std::string& data, characteristic_properties type) = 0;

            /**
             * @brief set_characteristic_notify
             * @param dev
             * @param srv
             * @param chr
             */
            virtual void set_characteristic_notify(device& dev,const service& srv, const characteristic& chr, bool notify) = 0;
        };
    }
}

#endif // CENTRALPLUGININTERFACE_H

