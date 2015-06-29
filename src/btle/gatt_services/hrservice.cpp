
#include "btle/gatt_services/hrservice.h"
#include "btle/gatt_services/gattserviceregisterer.h"

#include <stdio.h>
#include <sstream>
#include <cstring>

using namespace btle::gatt_services;

namespace {
    gattserviceregisterer<hrservice> registration;
}

hrservice::hrservice()
: hr_value_(0),
  rrs_(),
  energy_expended_(0)
{
    mandatory_notifications_.push_back(uuid(HEART_RATE_MEASUREMENT));
    included_characteristics_.push_back(uuid(HEART_RATE_MEASUREMENT));
    service_ = uuid(HEART_RATE_SERVICE);
}

/**
 * @brief hrservice::hr_value, current hr in bpm
 * @return
 */
int hrservice::hr_value() const
{
    return hr_value_;
}

/**
 * @brief hrservice::sensor_contact, contact status true ok false bad
 * @return
 */
bool hrservice::sensor_contact() const
{
    return flags_.sensor_contact_bit_ == 0x3;
}

/**
 * @brief hrservice::rr_values, rr values in milliseconds
 * @return
 */
const std::vector<int>& hrservice::rr_values() const
{
    return rrs_;
}

/**
 * @brief hrservice::energy_expeneded
 * @return
 */
int hrservice::energy_expeneded() const
{
    return energy_expended_;
}

void hrservice::process_service_notify_data(const uuid &chr, const uint8_t* data, size_t size)
{
    switch( chr.uuid16bit() )
    {
        case HEART_RATE_MEASUREMENT:
        {
            memset(&flags_,0,sizeof(flags_));
            memcpy(&flags_,data,sizeof(flags_));

            int offset(sizeof(flags_));
            memcpy(&hr_value_,&data[offset],flags_.hr_format_bit_+1);
            offset += flags_.hr_format_bit_+1;

            if ( flags_.energy_expended_bit_ )
            {
                memcpy(&energy_expended_,data+offset,sizeof(energy_expended_));
                offset += sizeof(energy_expended_);
            }

            rrs_.clear();
            if( flags_.rr_interval_bit_ )
            {
                while( offset < (int)size )
                {
                    int rr_value(0);
                    memcpy(&rr_value,data+offset,2);
                    double tmp=((double)rr_value/1024.0)*1000.0;
                    rr_value = (uint16_t)tmp;
                    rrs_.push_back(rr_value);
                    offset += 2;
                }
            }
            break;
        }
    }
}

void hrservice::process_service_value_read(const uuid &chr, const uint8_t *data, size_t size, const error &err)
{

}

void hrservice::reset()
{
    hr_value_ = 0;
    rrs_.clear();
    energy_expended_ = 0;
    memset(&flags_,0,sizeof(flags_));
}

std::string hrservice::json() const
{
    std::stringstream ss;
    ss << "{\n \"hrValue\", " << hr_value()
       << ",\n \"energyExpended\", " << energy_expeneded()
       << ",\n \"sensorContact\", " << sensor_contact()
       << ",\n \"rrValues\", [";
    
    for( std::vector<int>::const_iterator it = rr_values().begin(); it != rr_values().end(); ++it )
        ss << *it << ((it+1) != rr_values().end() ?  "," : "");
    
    ss << "]\n}";
    return ss.str();
}
