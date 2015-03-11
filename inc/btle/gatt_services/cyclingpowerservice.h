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

        struct powerflags
        {
            uint8_t pedal_power_balance_present_:1;
            uint8_t pedal_power_balance_reference_:1;
            uint8_t accumulated_torque_present_:1;
            uint8_t accumulated_torque_source_:1;
            uint8_t wheel_revolution_data_present_:1;
            uint8_t crank_revolution_data_present_:1;
            uint8_t extreme_force_magnitudes_present_:1;
            uint8_t extreme_torque_magnitudes_present_:1;
            uint8_t extreme_angles_present_:1;
            uint8_t top_dead_spot_angle_present_:1;
            uint8_t bottom_dead_spot_angle_present_:1;
            uint8_t accumulated_energy_present_:1;
            uint8_t offset_compensation_indicator_:1;
        };

        struct powerfeatureflags
        {
            uint8_t pedal_power_balance_present_:1;
            uint8_t accumulated_torque_present_:1;
            uint8_t wheel_revolution_data_present_:1;
            uint8_t crank_revolution_data_present_:1;
            uint8_t extreme_magnitudes_present_:1;
            uint8_t extreme_angles_present_:1;
            uint8_t top_dead_spot_angle_present_:1;
            uint8_t accumulated_energy_present_:1;
            uint8_t offset_compensation_indicator_:1;
            uint8_t offset_compensation_present_:1;
            uint8_t extreme_torque_magnitudes_present_:1;
            uint32_t reserved_:21;
        };

        struct powervectorflags
        {
            uint8_t crank_revolutions_present_:1;
            uint8_t first_crank_measurement_angle_present_:1;
            uint8_t inst_force_magnitude_array_present_:1;
            uint8_t inst_torque_magnitude_array_present_:1;
            uint8_t inst_measurement_direction_:2;
            uint8_t reserved_:2;
        };

        class cyclingpowerservice: public gattservicebase{
        public:
            cyclingpowerservice();

        public: // from base

            void process_service_data(const uuid& chr, const uint8_t* data, size_t size);

        private:

            uint16_t offset_compensation_indicator_;
            powerflags flags_;
            powervectorflags vector_flags_;
            int16_t inst_power_;
            double pedal_power_balance_;
            double accumulated_torque_;
            int16_t maximum_force_;
            int16_t minimum_force_;
            double maximum_torque_;
            double minimum_torque_;
            uint16_t maximum_angle_;
            uint16_t minimum_angle_;
            uint16_t top_dead_spot_angle_;
            uint16_t bottom_dead_spot_angle_;
            uint16_t accumulated_energy_;
            uint8_t response_value_;
            uint16_t first_cranck_measurement_angle_;
            double power_balance_;
            std::vector<int16_t> inst_force_magnitude_array_;
            std::vector<double> inst_torque_magnitude_array_;
        };
    }
}

#endif // CYCLINGPOWERSERVICE_H

