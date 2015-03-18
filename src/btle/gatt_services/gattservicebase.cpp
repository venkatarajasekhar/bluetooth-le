
#include "btle/gatt_services/gattservicebase.h"

using namespace btle::gatt_services;

gattservicebase::gattservicebase()
{
}


const btle::uuid_list& gattservicebase::included_characteristics() const
{
    return included_characteristics_;
}

const btle::uuid_list& gattservicebase::mandatory_notifications() const
{
    return mandatory_notifications_;
}

bool gattservicebase::contains_characteristic_uuid(const uuid& uid) const
{
    for( uuid_iterator_const it = included_characteristics_.begin(); it != included_characteristics_.end(); ++it )
    {
        if( (*it) == uid )
        {
            return true;
        }
    }
    return false;
}

const btle::uuid& gattservicebase::service_uuid() const
{
    return service_;
}
