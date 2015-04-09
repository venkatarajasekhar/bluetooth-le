
#include "btle/gatt_services/glucoseservice.h"
#include "btle/gatt_services/gattserviceregisterer.h"

#include <stdio.h>
#include <cstring>

using namespace btle::gatt_services;

namespace {
    gattserviceregisterer<glucoseservice> registration;
}

glucoseservice::glucoseservice()
{
    service_ = uuid(GLUCOSE_SERVICE);
    included_characteristics_.push_back(uuid(GLUCOSE_MEASUREMENT));
    mandatory_notifications_.push_back(uuid(GLUCOSE_MEASUREMENT));
}

void glucoseservice::process_service_notify_data(const uuid& chr, const uint8_t* data, size_t size)
{
    switch( chr.uuid16bit() )
    {
        case GLUCOSE_MEASUREMENT:
        {
            memset(&flags_,0,sizeof(flags_));
            memcpy(&flags_,data,sizeof(flags_));

            // int offset(sizeof(flags_));
            // TODO implement


            break;
        }
    }
}

void glucoseservice::process_service_value_read(const uuid& chr, const uint8_t* data, size_t size, const error& err)
{

}

void glucoseservice::reset()
{

}


