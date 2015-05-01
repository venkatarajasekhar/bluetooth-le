#ifndef PERIPHERALPLUGININTERFACE_H
#define PERIPHERALPLUGININTERFACE_H

#include "advertisementfields.h"

namespace btle {
    class service;
    class gattdatabase;
    namespace peripheral {
        class peripheralplugininterface{
        public:
            peripheralplugininterface();

        public:

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
             * @return
             */
            virtual std::vector<advertisement_data_type> supported_adtypes() = 0;
        };
    }
}

#endif // PERIPHERALPLUGININTERFACE_H

