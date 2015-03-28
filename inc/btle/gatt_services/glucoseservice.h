#ifndef GLUCOSESERVICE_H
#define GLUCOSESERVICE_H

#include "btle/gatt_services/gattservicebase.h"

namespace btle {
    namespace gatt_services {

        struct glucosefields
        {
            uint8_t time_offset_present_:1;
            uint8_t glucose_concentration_type_and_sample_location_present_:1;
            uint8_t glucose_concentration_units_:1;
            uint8_t sensor_status_annunciation_present_:1;
            uint8_t context_information_follows_:1;
            uint8_t reserved:3;
        };

        #define GLUCOSE_MEASUREMENT         0x2A18
        #define GLUCOSE_SERVICE             0x1808
        #define GLUCOSE_MEASUREMENT_CONTEXT 0x2A34

        class BTLE_API glucoseservice: public gattservicebase{
        public:
            glucoseservice();

        public:

            void process_service_notify_data(const uuid& chr, const uint8_t* data, size_t size);
            void process_service_value_read(const uuid& chr, const uint8_t* data, size_t size, const error& err);
            void reset();

        public: // api

        private:

            glucosefields flags_;
        };
    }
}

#endif // GLUCODESERVICE_H

