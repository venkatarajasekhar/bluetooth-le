
#include "btle/peripheral/peripheralplugininterface.h"

using namespace btle::peripheral;

peripheralplugininterface::peripheralplugininterface()
{
}

unsigned int peripheralplugininterface::features()
{
    return 0;
}

void peripheralplugininterface::discover_services(device& central)
{

}
