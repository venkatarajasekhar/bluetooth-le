
#include "btle/gatt_services/btlelibservice.h"
#include "btle/gatt_services/gattserviceregisterer.h"

using namespace btle::gatt_services;

namespace {
}

btlelibservice::btlelibservice()
{
    service_ = uuid(BTLE_SERVICE);
    mandatory_notifications_.push_back(uuid(BTLE_MTU));
    included_characteristics_.push_back(uuid(BTLE_VERSION));
    included_characteristics_.push_back(uuid(BTLE_MTU));
}

void btlelibservice::process_service_notify_data(const uuid& chr, const uint8_t* data, size_t size)
{
    
}

void btlelibservice::process_service_value_read(const uuid& chr, const uint8_t* data, size_t size, const error& err)
{
    
}

void btlelibservice::reset()
{
    
}
