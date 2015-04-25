
#include "btle/gatt_services/btlelibservice.h"
#include "btle/gatt_services/gattserviceregisterer.h"

using namespace btle::gatt_services;

namespace {
    #if 0
    gattserviceregisterer<btlelibservice> registration;
    #endif
    
    enum transfer_status
    {
        idle,
        
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
        switch(status_)
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
        }
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
    out_.push_back(data);
    
    return 0;
}

std::string btlelibservice::take_last_message() const
{
    return "";
}
