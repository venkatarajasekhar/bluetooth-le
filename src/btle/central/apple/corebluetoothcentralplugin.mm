
#include "btle/central/apple/corebluetoothcentralplugin.h"
#include "btle/central/centralpluginregisterer.h"

using namespace btle::central::apple;
using namespace btle::central;
using namespace btle;

namespace {
    centralpluginregisterer<corebluetoothcentralplugin> registration;
}


corebluetoothcentralplugin::corebluetoothcentralplugin(centralpluginobserver &observer)
: centralplugininterface(observer),
  base("","WIN8 central plugin implementation")
{

}

const std::string& corebluetoothcentralplugin::name()
{
    return "APPLE_CENTRAL";
}

std::vector<device*>& corebluetoothcentralplugin::devices()
{
    return devices_;
}

device* corebluetoothcentralplugin::allocate_new_device(const bda& addr)
{
    return NULL;
}

int corebluetoothcentralplugin::start()
{
    return 0;
}

void corebluetoothcentralplugin::stop()
{

}

void corebluetoothcentralplugin::start_scan( const uuid_list* services )
{

}

void corebluetoothcentralplugin::stop_scan()
{

}

void corebluetoothcentralplugin::connect_device(device& dev)
{

}

void corebluetoothcentralplugin::disconnect_device(device& dev)
{

}

void corebluetoothcentralplugin::cancel_pending_connection(device& dev)
{

}

void corebluetoothcentralplugin::discover_characteristics(device& dev, const service& srv)
{

}

void corebluetoothcentralplugin::read_characteristic_value(device& dev,const service& srv, const characteristic& chr)
{

}

void corebluetoothcentralplugin::write_characteristic_value(device& dev,const service& srv, const characteristic& chr, const std::string& data, characteristic_properties type)
{

}

void corebluetoothcentralplugin::set_characteristic_notify(device& dev,const service& srv, const characteristic& chr, bool notify)
{

}

void corebluetoothcentralplugin::write_descriptor(device& dev, const service& srv, const characteristic& chr, descriptor& desc, bool notify)
{

}

@implementation corebluetoothcentralpluginprivate

-(id) init:(corebluetoothcentralplugin*) plugin
{
    self = [super init];
    if(self)
    {

    }
    return self;
}

-(void) dealloc
{
}

- (void) centralManagerDidUpdateState:(CBCentralManager *)central
{
}

- (void) centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)aPeripheral advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI
{
}

- (void)centralManager:(CBCentralManager *)central didRetrievePeripherals:(NSArray *)peripherals
{
}

- (void)centralManager:(CBCentralManager *)central didRetrieveConnectedPeripherals:(NSArray *)peripherals
{
}

- (void) centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)aPeripheral
{
}

- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)aPeripheral error:(NSError *)error
{
}

- (void)centralManager:(CBCentralManager *)central didFailToConnectPeripheral:(CBPeripheral *)aPeripheral error:(NSError *)error
{
}

//
- (void) peripheral:(CBPeripheral *)aPeripheral didDiscoverServices:(NSError *)error
{
}

- (void) peripheral:(CBPeripheral *)aPeripheral didDiscoverCharacteristicsForService:(CBService *)service error:(NSError *)error
{
}

- (void) peripheral:(CBPeripheral *)aPeripheral didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error
{
}

- (void)peripheralDidUpdateRSSI:(CBPeripheral *)aPeripheral error:(NSError *)error
{
}

- (void)peripheral:(CBPeripheral *)aPeripheral didUpdateNotificationStateForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error
{
}

- (void)peripheral:(CBPeripheral *)aPeripheral didWriteValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error
{
}

-(void)peripheral:(CBPeripheral *)peripheral didDiscoverDescriptorsForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error
{
}

- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForDescriptor:(CBDescriptor *)descriptor error:(NSError *)error
{
}

- (void)peripheral:(CBPeripheral *)peripheral didWriteValueForDescriptor:(CBDescriptor *)descriptor error:(NSError *)error
{
}

@end

