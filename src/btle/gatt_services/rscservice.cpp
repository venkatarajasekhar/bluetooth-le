
#include "btle/gatt_services/rscservice.h"
#include <stdio.h>

using namespace btle::gatt_services;

rscservice::rscservice()
{
    mandatory_notifications_.push_back(uuid(RSC_MEASUREMENT));
    service_ = (RSC_SERVICE);
}

double rscservice::speed() const
{
    return speed_;
}

int rscservice::cadence() const
{
    return cadence_;
}

uint16_t rscservice::stride_length() const
{
    return stride_length_;
}

double rscservice::distance() const
{
    return distance_;
}

void rscservice::process_service_data(const uuid& chr, const uint8_t* data, size_t size)
{
    switch(chr.uuid16bit())
    {
        case RSC_MEASUREMENT:
        {
            int offset(1);
            //memset(&flags_,0,sizeof(flags_));
            memcpy(&flags_,data,sizeof(flags_));

            uint16_t speed_mask(0);
            memcpy(&speed_mask, data+offset, sizeof(speed_mask));
            speed_ = ((double)speed_mask/256.0)*3.6;
            offset += sizeof(speed_mask);
            cadence_ = *(data + offset);
            offset += sizeof(uint8_t);
            stride_length_ = 0;
            distance_ = 0;
            if( flags_.stride_length_present_ )
            {
                memcpy(&stride_length_, data+offset, sizeof(stride_length_));
                offset += sizeof(stride_length_);
            }
            if( flags_.distance_present_ )
            {
                uint32_t distance_tmp(0);
                memcpy(&distance_tmp, data+offset, sizeof(distance_tmp));
                distance_ = ((double)distance_tmp*0.1);
            }
            break;
        }
    }
}


