
#include "peripheral/apple/corebluetoothperipheralplugin.h"

using namespace btle;
using namespace btle::peripheral;
using namespace btle::peripheral::apple;

corebluetoothperipheralplugin::corebluetoothperipheralplugin()
{
}

unsigned int corebluetoothperipheralplugin::features()
{
    return 0;
}

const std::string& corebluetoothperipheralplugin::name()
{
    return "";
}

int corebluetoothperipheralplugin::start()
{
    return -1;
}

void corebluetoothperipheralplugin::stop()
{

}

peripheralplugininterface& corebluetoothperipheralplugin::operator << (const service& srv)
{
    return *this;
}

void corebluetoothperipheralplugin::start_advertising(int ms,const adv_fields& fields)
{

}

void corebluetoothperipheralplugin::stop_advertising()
{

}

std::vector<advertisement_data_type> corebluetoothperipheralplugin::supported_adtypes()
{
    std::vector<advertisement_data_type> types;
    return types;
}

std::string corebluetoothperipheralplugin::read_characteristic(device& central, characteristic& chr)
{
    return "";
}

void corebluetoothperipheralplugin::characteristic_written(device& central, characteristic& chr)
{

}

std::string corebluetoothperipheralplugin::read_descriptor(device& central, characteristic& chr, descriptor& desc)
{
    return "";
}

std::string corebluetoothperipheralplugin::descriptor_written(device& central, characteristic& chr, descriptor& desc)
{
    return "";
}

void corebluetoothperipheralplugin::characteristic_notify_changed(device& central, characteristic& srv, bool notify)
{
}
