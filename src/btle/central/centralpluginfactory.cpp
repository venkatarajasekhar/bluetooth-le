
#include "btle/central/centralpluginfactory.h"

using namespace btle::central;

centralpluginfactory& centralpluginfactory::instance()
{
    static centralpluginfactory instance;
    return instance;
}

void centralpluginfactory::populate(std::vector<centralplugininterface*> &plugins,
                                    centralpluginobserver& observer)
{
    for( std::vector<plugin_constructor>::iterator it = constructors_.begin(); it != constructors_.end(); ++it )
    {
        plugin_constructor create = (plugin_constructor)*it;
        plugins.push_back( (*create)(observer) );
    }
}

void centralpluginfactory::deplete(std::vector<centralplugininterface*> &plugins)
{
    for(std::vector<centralplugininterface*>::iterator it = plugins.begin(); it != plugins.end(); ++it )
    {
        delete (*it);
    }
    plugins.clear();
}

centralpluginfactory::centralpluginfactory()
: constructors_()
{
}

void centralpluginfactory::insert(plugin_constructor constructor)
{
    constructors_.push_back(constructor);
}
