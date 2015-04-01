
#include "btle/central/centralplugininterface.h"

using namespace btle::central;

centralplugininterface::centralplugininterface(centralpluginobserver &observer)
: observer_(observer)
{
}

centralplugininterface::~centralplugininterface()
{
}

unsigned int centralplugininterface::features()
{
    return 0;
}


