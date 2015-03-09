
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

