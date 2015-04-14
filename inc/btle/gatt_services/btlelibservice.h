
#ifndef btle_btlelibservice_h
#define btle_btlelibservice_h

#include "btle/gatt_services/gattservicebase.h"

namespace btle {
    namespace gatt_services{
        /**
         * btle library service for data transfer between two devices running the library
         */
        class btlelibservice: public gattservicebase{
        public:
            btlelibservice();
            
        public:
            
            void process_service_notify_data(const uuid& chr, const uint8_t* data, size_t size);
            void process_service_value_read(const uuid& chr, const uint8_t* data, size_t size, const error& err);
            void reset();
        };
    }
}

#endif
