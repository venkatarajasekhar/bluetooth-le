#ifndef PERIPHERALPLUGININTERFACE_H
#define PERIPHERALPLUGININTERFACE_H

#include "advertisementfields.h"

namespace btle {
    class service;
    class gattdatabase;
    class device;
    class service;
    class characteristic;
    class descriptor;
    namespace peripheral {

        class peripheralpluginobserver;

        enum peripheral_plugin_extras
        {
            PLUGIN_CENTRAL_GATT_DISCOVERY_CAPABILITY = 0x01
        };

        class peripheralplugininterface{
        public:
            peripheralplugininterface();

        public:

            /**
             * @brief features
             * @return @see central_plugin_extras, returns bit mask of extra features if any
             */
            virtual unsigned int features();

            /**
             * @brief name
             * @return
             */
            virtual const std::string& name() = 0;

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
             * @brief operator <<
             * @param srv
             * @return
             */
            virtual peripheralplugininterface& operator << (const service& srv) = 0;

            /**
             * @brief start_advertising
             * @param ms interval in milliseconds, though this is just a wish
             * @param fields
             */
            virtual void start_advertising(int ms,const adv_fields& fields) = 0;

            /**
             * @brief stop_advertising
             */
            virtual void stop_advertising() = 0;

            /**
             * @brief supported_adtypes
             * @return plugin supported ad types, it is common that not all ad types are supported, it depends on platform or
             *         hw etc...
             */
            virtual std::vector<advertisement_data_type> supported_adtypes() = 0;

            /**
             * @brief read_characteristic
             * @param central
             * @param chr
             * @return
             */
            virtual std::string read_characteristic(device& central, characteristic& chr) = 0;

            /**
             * @brief characteristic_written
             * @param central
             * @param chr
             */
            virtual void characteristic_written(device& central, characteristic& chr) = 0;

            /**
             * @brief read_descriptor
             * @param central
             * @param chr
             * @param desc
             */
            virtual std::string read_descriptor(device& central, characteristic& chr, descriptor& desc) = 0;

            /**
             * @brief descriptor_written
             * @param central
             * @param chr
             * @param desc
             * @return
             */
            virtual std::string descriptor_written(device& central, characteristic& chr, descriptor& desc) = 0;

            /**
             * @brief did_subscribe_to_characteristic
             * @param central
             * @param srv
             */
            virtual void characteristic_notify_changed(device& central, characteristic& srv, bool notify) = 0;

            /**
             * @brief discover_services, optional service discovery, for discovering services of central device
             * @param central
             */
            virtual void discover_services(device& central);
        };
    }
}

#endif // PERIPHERALPLUGININTERFACE_H

