
#include "btle/gatt_services/hrservice.h"

#include <stdio.h>

using namespace btle::gatt_services;

hrservice::hrservice()
{
    mandatory_notifications_.push_back(uuid(HEART_RATE_MEASUREMENT));
    service_ = uuid(HEART_RATE_SERVICE);
}

int hrservice::hr_value() const
{
    return hr_value_;
}

void hrservice::process_service_data(const uuid &chr, const uint8_t* data, size_t size)
{
    switch( chr.uuid16bit() )
    {
        case HEART_RATE_MEASUREMENT:
        {
            btle::gatt_services::hrfields flags_={0};
            memcpy(&flags_,data,sizeof(flags_));

            int offset(sizeof(flags_));
            memcpy(&hr_value_,data+offset,flags_.hr_format_bit_+1);
            offset += flags_.hr_format_bit_+1;

            if ( flags_.energy_expended_bit_ )
            {
                uint16_t energy_expended_(0);
                memcpy(&energy_expended_,data+offset,sizeof(energy_expended_));
                offset += sizeof(energy_expended_);
            }

            if( flags_.rr_interval_bit_ )
            {
                while( offset < (int)size )
                {
                    int rr_value(0);
                    memcpy(&rr_value,data+offset,2);
                    double tmp=((double)rr_value/1024.0)*1000.0;
                    rr_value = (uint16_t)tmp;
                }
            }
            break;
        }
    }
}


