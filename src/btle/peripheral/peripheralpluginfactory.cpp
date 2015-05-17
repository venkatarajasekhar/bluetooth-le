
#include "btle/peripheral/peripheralpluginfactory.h"

using namespace btle::peripheral;

peripheralpluginfactory& peripheralpluginfactory::instance()
{
    static peripheralpluginfactory instance;
    return instance;
}

void peripheralpluginfactory::populate(std::vector<peripheralplugininterface*> &plugins,
                                    peripheralpluginobserver& observer)
{
    for( std::vector<plugin_constructor>::iterator it = constructors_.begin(); it != constructors_.end(); ++it )
    {
        plugin_constructor create = (plugin_constructor)*it;
        plugins.push_back( (*create)(observer) );
    }
}

void peripheralpluginfactory::deplete(std::vector<peripheralplugininterface*> &plugins)
{
    for(std::vector<peripheralplugininterface*>::iterator it = plugins.begin(); it != plugins.end(); ++it )
    {
        delete (*it);
    }
    plugins.clear();
}

peripheralpluginfactory::peripheralpluginfactory()
: constructors_()
{
}

void peripheralpluginfactory::insert(plugin_constructor constructor)
{
    constructors_.push_back(constructor);
}

