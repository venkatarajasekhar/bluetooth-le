#ifndef RSCSERVICE_H
#define RSCSERVICE_H

#include "btle/gatt_services/gattservicebase.h"

namespace btle {
    namespace gatt_services {

        /**
         * @brief The rsc_cs_operation enum, control point operation definations
         */
        enum rsc_cs_operation
        {
            RSC_CS_FAILED                              = -1,
            RSC_CS_NONE                                = 0x00,
            RSC_CS_SET_CUMULATIVE_VALUE                = 0x01,
            RSC_CS_START_SENSOR_CALIBRATION            = 0x02,
            RSC_CS_UPDATE_SENSOR_LOCATION              = 0x03,
            RSC_CS_REQ_SUPPORTED_SENSOR_LOCATIONS      = 0x04
        };

        /**
         * @brief The rscfields struct,
         */
        struct rscfields
        {
            uint8_t stride_length_present_:1;
            uint8_t distance_present_:1;
            uint8_t walking_status_:1;
            uint8_t reserved_:5;
        };

        #define RSC_SERVICE                 0x1814
        #define RSC_MEASUREMENT             0x2A53
        #define RSC_FEATURE                 0x2A54
        #define RSC_SENSOR_LOCATION         0x2A5D
        #define RSC_CS_CONTROL_POINT        0x2A55

        class rscservice: public gattservicebase{
        public:
            rscservice();

        public: // api

            double speed() const;
            int cadence() const;
            uint16_t stride_length() const;
            double distance() const;

        public:

            void process_service_data(const uuid& chr, const uint8_t* data, size_t size);

        private:

            double speed_;
            int cadence_;
            uint16_t stride_length_;
            double distance_;
            rscfields flags_;
            rsc_cs_operation pending_operation_;
            rsc_cs_operation completed_operation_;
            std::vector<uint8_t> slocations_;
            uint8_t sensor_location_;
        };
    }
}
#endif // RSCSERVICE_H

