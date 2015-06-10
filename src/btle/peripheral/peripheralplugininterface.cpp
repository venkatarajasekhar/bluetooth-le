
#include "btle/peripheral/peripheralplugininterface.h"

using namespace btle::peripheral;

peripheralplugininterface::peripheralplugininterface(peripheralpluginobserver& observer)
: observer_(observer)
{
}

unsigned int peripheralplugininterface::features()
{
    return 0;
}

void peripheralplugininterface::discover_services(device& central)
{

}

void peripheralplugininterface::discover_characteristics(device& central, const service& srv)
{

}

void peripheralplugininterface::read_characteristic_value(device& central, const service& srv, const characteristic& chr)
{

}

