#ifndef HRSERVICE_H
#define HRSERVICE_H

#include "btle/gatt_services/gattservicebase.h"

namespace btle {
    namespace gatt_services {

        struct hrfields
        {
            uint8_t hr_format_bit_:1;
            uint8_t sensor_contact_bit_:2;
            uint8_t energy_expended_bit_:1;
            uint8_t rr_interval_bit_:1;
            uint8_t reserved_:3;
        };

        #define HEART_RATE_SERVICE          0x180D
        #define HEART_RATE_MEASUREMENT      0x2A37
        #define HEART_RATE_CONTROL_POINT    0x2A39

        class BTLE_API hrservice: public gattservicebase{
        public:
            hrservice();

        public:

            void process_service_notify_data(const uuid& chr, const uint8_t* data, size_t size);
            void process_service_value_read(const uuid& chr, const uint8_t* data, size_t size, const error& err);
            void reset();

        public: // api

            int hr_value() const;
            bool sensor_contact() const;
            const std::vector<int>& rr_values() const;
            int energy_expeneded() const;

        private:

            int hr_value_;
            hrfields flags_;
            std::vector<int> rrs_;
            uint16_t energy_expended_;
        };
    }
}
#endif // HRSERVICE_H

