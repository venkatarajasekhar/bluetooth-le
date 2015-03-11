
#include "btle/gatt_services/cyclingpowerservice.h"
#include <cstring>

using namespace btle::gatt_services;

cyclingpowerservice::cyclingpowerservice()
{

}

void cyclingpowerservice::process_service_data(const uuid &chr, const uint8_t *data, size_t size)
{
    switch( chr.uuid16bit() )
    {
        case CYCLING_POWER_MEASUREMENT:
        {
            memset(&flags_,0,sizeof(flags_));
            memcpy(&flags_,data,sizeof(flags_));
            int offset(sizeof(flags_));
            memcpy(&inst_power_,data+offset,sizeof(inst_power_));
            offset += sizeof(inst_power_);

            if( flags_.pedal_power_balance_present_ )
            {
                uint8_t pedal_power_balance = *(data+offset);
                pedal_power_balance_ = (double)pedal_power_balance/2;
                offset += sizeof(uint8_t);
            }
            if( flags_.accumulated_torque_present_ )
            {
                uint16_t accumulated_torque(0);
                memcpy(&accumulated_torque,data+offset,sizeof(accumulated_torque));
                accumulated_torque_ = (double)accumulated_torque/32;
                offset += sizeof(accumulated_torque);
            }
            if( flags_.wheel_revolution_data_present_ )
            {
                // TODO
            }
            if( flags_.crank_revolution_data_present_ )
            {
                // TODO
            }
            if( flags_.extreme_force_magnitudes_present_ )
            {
                memcpy(&maximum_force_,data+offset,sizeof(maximum_force_));
                offset += sizeof(maximum_force_);
                memcpy(&minimum_force_,data+offset,sizeof(minimum_force_));
                offset += sizeof(minimum_force_);
            }
            if( flags_.extreme_torque_magnitudes_present_ )
            {
                int16_t maximum_torque(0);
                memcpy(&maximum_torque,data+offset,sizeof(maximum_torque));
                maximum_torque_ = (double)maximum_torque/32;
                offset += sizeof(maximum_torque);

                int16_t minimum_torque(0);
                memcpy(&minimum_torque,data+offset,sizeof(minimum_torque));
                minimum_torque_ = (double)minimum_torque/32;
                offset += sizeof(minimum_torque);
            }
            if( flags_.extreme_angles_present_ )
            {
                uint32_t angles = 0;
                memcpy(&angles, data+offset, 3);
                maximum_angle_ = angles & 0x000FFF;
                minimum_angle_ = (angles & 0xFFF000) >> 12;
                offset += 3;
            }
            if( flags_.top_dead_spot_angle_present_ )
            {
                memcpy(&top_dead_spot_angle_,data+offset,sizeof(top_dead_spot_angle_));
                offset += sizeof(top_dead_spot_angle_);
            }
            if( flags_.bottom_dead_spot_angle_present_ )
            {
                memcpy(&bottom_dead_spot_angle_,data+offset,sizeof(bottom_dead_spot_angle_));
                offset += sizeof(bottom_dead_spot_angle_);
            }
            if( flags_.accumulated_energy_present_ )
            {
                memcpy(&accumulated_energy_,data+offset,sizeof(accumulated_energy_));
            }
            break;
        }
    }
}
