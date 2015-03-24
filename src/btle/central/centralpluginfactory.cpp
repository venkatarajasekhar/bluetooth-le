
#include "btle/central/centralpluginfactory.h"

using namespace btle::central;

centralpluginfactory& centralpluginfactory::instance()
{
    centralpluginfactory instance;
    return instance;
}

void centralpluginfactory::populate(std::vector<centralplugininterface> &plugins)
{

}

void centralpluginfactory::deplete(std::vector<centralplugininterface> &plugins)
{

}

centralpluginfactory::centralpluginfactory()
{
}

void centralpluginfactory::insert(plugin_constructor constructor)
{

}
