
#include "btle/gatt_services/gattservicebase.h"

using namespace btle::gatt_services;

gattservicebase::gattservicebase()
{
}

gattservicebase::~gattservicebase()
{
}

void gattservicebase::set_active(const uuid& uid, bool notifying)
{

}

int gattservicebase::write_service_value(const uuid& chr, const std::string& data)
{
    return -1;
}

bool gattservicebase::is_active() const
{
    return false;
}

/**
 * @brief gattservicebase::json, optional (NOTE will not be supported in 1.x.x version)
 *                               to get e.g. Heart rate measurement in json
 *                               to be passed to remote server
 * @param uid
 * @return
 */
std::string gattservicebase::json(const uuid& uid) const
{
    return "";
}

void gattservicebase::attach_service_resource(const service& srv)
{
    service_resource_ = srv;
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
