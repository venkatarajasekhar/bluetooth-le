
#ifndef btle_btlelibservice_h
#define btle_btlelibservice_h

#include "btle/gatt_services/gattservicebase.h"

namespace btle {
    namespace gatt_services{
        /**
         * btle library service for data transfer between two devices running the library
         */
        #define BTLE_SERVICE "\x42\x54\x4c\x45\x20\x4c\x49\x42\x20\x53\x45\x52\x56\x49\x43\x45"
        #define BTLE_MTU     "\x42\x54\x4c\x45\x20\x43\x48\x52\x20\x4d\x54\x55\x20\x31\x32\x38"
        #define BTLE_VERSION "\x42\x54\x4c\x45\x20\x43\x48\x52\x20\x46\x45\x41\x54\x55\x52\x45"
        
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
