
#include "btle/central/collector.h"
#include "btle/exceptions/attribute_not_found.h"
#include "btle/exceptions/attribute_not_readable.h"
#include "btle/exceptions/device_not_connected.h"
#include "btle/gatt_services/gattservicefactory.h"

using namespace btle::central;

collector::collector()
{
    gatt_services::gatt_list services;
    gatt_services::gattservicefactory::instance().populate(services);
    for( gatt_services::gatt_list::iterator it = services.begin(); it != services.end(); ++it )
    {

       // notify_uuids_.push_back();
    }
    gatt_services::gattservicefactory::instance().deplete(services);
}

void collector::set_scan_filter(const uuid_list& filter)
{

}

void collector::set_scan_filter(const bda_list &bdas)
{

}

void collector::start_scan()
{

}

void collector::stop_scan()
{

}

void collector::auto_connect(const bda& addr)
{

}

void collector::connect_device(device& dev)
{

}

void collector::disconnect_device(device& dev)
{

}

void collector::disconnect_device(const bda& addr)
{

}

void collector::read_characteristic_value(device& dev, const uuid& uid)
{
    if( dev.state() != btle::DEVICE_CONNECTED )
    {
        if( const characteristic* chr = dev.db().fetch_characteristic(uid) )
        {
            if( chr->properties() & btle::GATT_READ )
            {
                // TODO
                return;
            }
            throw btle::exceptions::attribute_not_readable("attribute cannot be read");
        }
        throw btle::exceptions::attribute_not_found("device does not contain this uuid");
    }
    throw btle::exceptions::device_not_connected("device not connected");
}

void collector::read_characteristic_value(device& dev, const uuid_pair& pair)
{

}

void collector::write_characteristic_value(device& dev, const uuid& uid)
{

}

void collector::write_characteristic_value(device& dev, const uuid_pair& pair)
{

}

void collector::set_characteristic_notify(device& dev, const uuid& uid, bool notify)
{

}

void collector::set_characteristic_notify(device& dev, const uuid_pair& pair, bool notify)
{

}
