
#include "btle/uuidscanfilter.h"

using namespace btle;

uuidscanfilter::uuidscanfilter(const uuid_list& uuids)
: scanfilterbase("Uuid based scan filer"),
  uuids_(uuids)
{
}

uuidscanfilter::uuidscanfilter(const uuidscanfilter& other)
: scanfilterbase(other),
  uuids_(other.uuids_)
{
}

bool uuidscanfilter::process(device &dev,adv_fields& fields,int rssi)
{
    for( uuid_iterator_const it = uuids_.begin(); it != uuids_.end(); ++it )
    {
        if( dev.advertisement_fields().is_service_advertiset((*it)) )
        {
            return true;
        }
    }
    return false;
}


