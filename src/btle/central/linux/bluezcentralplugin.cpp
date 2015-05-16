

#include "btle/central/linux/bluezcentralplugin.h"
#include "btle/central/centralpluginregisterer.h"
#include "btle/log.h"

#include <sys/ioctl.h>
#include <stdio.h>

#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

using namespace btle::central::linux_platform;
using namespace btle::central;
using namespace btle;

namespace {
    centralpluginregisterer<bluezcentralplugin> registration;

}

bluezcentralplugin::bluezcentralplugin(centralpluginobserver &observer)
: centralplugininterface(observer),
  base("","LINUX central plugin implementation")
{

}

const std::string& bluezcentralplugin::name()
{
    return "LINUX_CENTRAL";
}

std::vector<device*>& bluezcentralplugin::devices()
{
    return devices_;
}

device* bluezcentralplugin::allocate_new_device(const bda& addr)
{
    return NULL;
}

int bluezcentralplugin::start()
{
    id_ = hci_get_route(NULL);
    int on = 1;
    if((handle_ = hci_open_dev(id_)) == 0)
    {
        if( ioctl(handle_, FIONBIO, (char *)&on) == 0)
        {
            return 0;
        }
        else return -1;
    }
    else return handle_;
}

void bluezcentralplugin::stop()
{

}

void bluezcentralplugin::start_scan( const uuid_list* services )
{
    // TODO change from full window to approx. 80%
    int err(0);
    if( (err = hci_le_set_scan_parameters(handle_, 0x01, htobs(0x0010), htobs(0x0010), 0x00, 0x00, 1000)) == 0)
    {
        if( (err = hci_le_set_scan_enable(handle_, 0x01, 1, 1000)) == 0)
        {

        }
        else _log_error(" err: %i",err);
    }
    else _log_error(" err: %i",err);
}

void bluezcentralplugin::stop_scan()
{

}

void bluezcentralplugin::connect_device(device& dev)
{

}

void bluezcentralplugin::disconnect_device(device& dev)
{

}

void bluezcentralplugin::cancel_pending_connection(device& dev)
{

}

void bluezcentralplugin::discover_services(device& dev)
{

}

void bluezcentralplugin::discover_characteristics(device& dev, const service& srv)
{

}

void bluezcentralplugin::read_characteristic_value(device& dev,const service& srv, const characteristic& chr)
{

}

void bluezcentralplugin::write_characteristic_value(device& dev,const service& srv, const characteristic& chr, const std::string& data, characteristic_properties type)
{

}

void bluezcentralplugin::set_characteristic_notify(device& dev,const service& srv, const characteristic& chr, bool notify)
{

}

void bluezcentralplugin::write_descriptor(device& dev, const service& srv, const characteristic& chr, descriptor& desc, bool notify)
{
    switch( desc.type() )
    {
        case CLIENT_CHARACTERISTIC_CONFIGURATION:
        {
            // TODO
            break;
        }
        case SERVER_CHARACTERISTIC_CONFIGURATION:
        {
            // TODO
            break;
        }
        default:
            break; // TODO throw not_implemented
    }
}


