
#include "btle/central/centralplugininterface.h"
#include <assert.h>

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

void centralplugininterface::update_parameters(device& dev, const connectionparameters& params)
{
    assert(!(features() & PLUGIN_CONNECTION_PARAMETER_CAPABILITY));
}

