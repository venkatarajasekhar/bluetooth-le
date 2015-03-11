#ifndef CSCSERVICE_H
#define CSCSERVICE_H

#include "btle/gatt_services/gattservicebase.h"

namespace btle {
    namespace gatt_services {

        /**
         * @brief The rsc_cs_operation enum, control point operation definations
         */
        enum csc_cs_operation
        {
            CSC_CS_FAILED                              = -1,
            CSC_CS_NONE                                = 0x00,
            CSC_CS_SET_CUMULATIVE_VALUE                = 0x01,
            CSC_CS_START_SENSOR_CALIBRATION            = 0x02,
            CSC_CS_UPDATE_SENSOR_LOCATION              = 0x03,
            CSC_CS_REQ_SUPPORTED_SENSOR_LOCATIONS      = 0x04
        };

        /**
         * @brief The cscfields struct
         */
        struct cscfields
        {
            uint8_t wheel_revolutions_present_:1;
            uint8_t cranck_revolutions_present_:1;
            uint8_t reserved_:6;
        };

        #define CSC_SERVICE                0x1816
        #define CSC_MEASUREMENT            0x2A5B
        #define CSC_FEATURE                0x2A5C
        #define CSC_SENSOR_LOCATION        0x2A5D
        #define CSC_CONTOROL_POINT         0x2A55

        // CSC specific
        #define CSC_MIN_SPEED_VALUE 2.0
        #define CSC_MAX_CEVENT_TIME 4
        #define CSC_MAX_EVENT_TIME  64.0
        #define CSC_SPEED_UNINIT    -1
        #define CSC_CADENCE_UNINT   -1

        class cscservice: public gattservicebase{
        public:
            cscservice();

        public: // api

        public: // from base

            void process_service_data(const uuid& chr, const uint8_t* data, size_t size);

        protected:

            int process_speed_measurement(const uint8_t *msg, int offset);
            int process_cadence_measurement(const uint8_t* msg, int offset);

        public: // API

            const cscfields& csc_flags();
            double speed();
            int cadence();
            double distance();
            double total_distance();
            bool is_speed_present();
            bool is_cadence_present();
            unsigned int wheel_revolutions();
            unsigned int cranck_revolutions();
            csc_cs_operation completed_operation();

        private:


            cscfields flags_;
            int wheel_size_;
            unsigned int curr_wheel_revs_;
            unsigned int curr_crank_revs_;
            double distance_;
            double total_distance_;
            double prev_wheel_event_;
            double curr_wheel_event_;
            double curr_crank_event_;
            double prev_crank_event_;
            unsigned int prev_wheel_revs_;
            unsigned int prev_crank_revs_;
            unsigned int exer_wheel_revs_;
            unsigned int wheel_rounds_;
            time_t wheel_event_;
            time_t crank_event_;
            double speed_;
            int cadence_;
            csc_cs_operation pending_operation_;
            csc_cs_operation completed_operation_;
            int max_wheel_time_;
        };
    }
}
#endif // CSCSERVICE_H

