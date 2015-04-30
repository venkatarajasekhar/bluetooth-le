
#include "btle/btlelibscanfilter.h"
#include "btle/gatt_services/btlelibservice.h"

using namespace btle;

btlelibscanfilter::btlelibscanfilter()
: scanfilterbase("BTLE lib scan filter for scanning btle library service"){
}

btlelibscanfilter::btlelibscanfilter(const btlelibscanfilter& other)
: scanfilterbase(other)
{
}

bool btlelibscanfilter::process(device &dev, adv_fields &fields, int rssi)
{
    return dev.advertisement_fields().is_service_advertiset(uuid(BTLE_SERVICE));
}





