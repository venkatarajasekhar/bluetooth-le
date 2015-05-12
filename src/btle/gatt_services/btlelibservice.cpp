
#include "btle/gatt_services/btlelibservice.h"
#include "btle/gatt_services/gattserviceregisterer.h"

#include <assert.h>

using namespace btle::gatt_services;

namespace {
    #if 0
    gattserviceregisterer<btlelibservice> registration;
    #endif
    
    enum transfer_status
    {
        idle,
        first_air_packet,
        streaming_in,
        streaming_out
    };
}

btlelibservice::btlelibservice()
: gattservicebase(),
  out_(),
  in_()
{
    service_ = uuid(BTLE_SERVICE);
    mandatory_notifications_.push_back(uuid(BTLE_MTU));
    included_characteristics_.push_back(uuid(BTLE_VERSION));
    included_characteristics_.push_back(uuid(BTLE_MTU));
}

void btlelibservice::process_service_notify_data(const uuid& chr, const uint8_t* data, size_t size)
{
    if( chr == BTLE_MTU )
    {
        /*switch(status_)
        {
            msg_payload payload = {0};
            memcpy(&payload, data, size);
            if( payload.more )
            {
                
            }
            else
            {
                // more = false, check all payload received
            }
        }*/
    }
}

void btlelibservice::process_service_value_read(const uuid& chr, const uint8_t* data, size_t size, const error& err)
{
    if( chr == BTLE_VERSION )
    {
        
    }
}

void btlelibservice::reset()
{
    
}

int btlelibservice::write_service_value(const uuid& chr, const std::string& data)
{
    assert(chr == BTLE_MTU);
    out_.push_back(data);
    if(status_ == idle)
    {
        // ok to start new transfer
        first_air_packet sof = {0};
        sof.more = true;
        sof.first = true;
        sof.rc = 0;
    }
    return 0;
}

std::string btlelibservice::take_last_message() const
{
    return "";
}
