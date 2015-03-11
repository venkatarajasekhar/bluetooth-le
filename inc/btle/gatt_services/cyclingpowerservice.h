#ifndef CYCLINGPOWERSERVICE_H
#define CYCLINGPOWERSERVICE_H


#include "btle/gatt_services/gattservicebase.h"


namespace btle {
    namespace gatt_services {

        #define CYCLING_POWER_SERVICE         0x1818
        #define CYCLING_POWER_MEASUREMENT     0x2A63
        #define CYCLING_POWER_CP              0x2A66
        #define CYCLING_POWER_VECTOR          0x2A64
        #define CYCLING_POWER_FEATURE         0x2A65
        #define CYCLING_POWER_SENSOR_LOCATION 0x2A5D

        class cyclingpowerservice: public gattservicebase{
        public:
            cyclingpowerservice();


        public: // from base

            void process_service_data(const uuid& chr, const uint8_t* data, size_t size);

        };
    }
}

#endif // CYCLINGPOWERSERVICE_H

