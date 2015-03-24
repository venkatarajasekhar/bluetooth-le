
#include "btle/gatt_services/gattservicefactory.h"

using namespace btle::gatt_services;

gattservicefactory& gattservicefactory::instance()
{
    static gattservicefactory instance;
    return instance;
}

void gattservicefactory::populate(std::vector<gattservicebase*>& services)
{
    for( std::vector<service_constructor>::iterator it = constructors_.begin(); it != constructors_.end(); ++it )
    {
        service_constructor create = (service_constructor)*it;
        services.push_back( (*create)() );
    }
}

void gattservicefactory::deplete(std::vector<gattservicebase*>& services)
{
    for(std::vector<gattservicebase*>::iterator it = services.begin(); it != services.end(); ++it )
    {
        delete (*it);
    }
    services.clear();
}

gattservicefactory::gattservicefactory()
: constructors_()
{
}

void gattservicefactory::insert(service_constructor constructor)
{
    constructors_.push_back(constructor);
}


