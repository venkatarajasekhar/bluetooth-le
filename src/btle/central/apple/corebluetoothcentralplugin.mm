
#include "btle/central/apple/corebluetoothcentralplugin.h"
#include "btle/central/centralpluginregisterer.h"

using namespace btle::central::apple;
using namespace btle::central;
using namespace btle;

namespace {
    centralpluginregisterer<corebluetoothcentralplugin> registration;
    
    
}


@implementation corebluetoothcentralpluginprivate

@synthesize manager_;

-(id) init:(corebluetoothcentralplugin*) plugin
{
    self = [super init];
    if(self)
    {
        parent_ = plugin;
        manager_ = [[CBCentralManager alloc] initWithDelegate:self queue:nil];
    }
    return self;
}

-(void) dealloc
{
}

- (void) centralManagerDidUpdateState:(CBCentralManager *)central
{
    // TODO
    switch ([central state]) {
        case CBCentralManagerStatePoweredOn:
        case CBCentralManagerStatePoweredOff:
        case CBCentralManagerStateResetting:
        case CBCentralManagerStateUnauthorized:
        case CBCentralManagerStateUnknown:
        case CBCentralManagerStateUnsupported:
        default:
            break;
    }
}

- (void) centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)aPeripheral advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI
{
    corebluetoothperipheraldevice* dev = parent_->find_device(aPeripheral);
    if( dev == NULL )
    {
        dev = new corebluetoothperipheraldevice(std::string([[[aPeripheral identifier] UUIDString] UTF8String]));
        parent_->devices().push_back(dev);
    }
    
    parent_->observer().device_discovered(*dev);
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

corebluetoothcentralplugin::corebluetoothcentralplugin(centralpluginobserver &observer)
: centralplugininterface(observer),
  base("","CoreBluetooth central plugin implementation")
{
}

const std::string& corebluetoothcentralplugin::name()
{
    static std::string name = "APPLE";
    return name;
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
    privateimpl_ = [[corebluetoothcentralpluginprivate alloc] init: this];
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

centralpluginobserver& corebluetoothcentralplugin::observer()
{
    return observer_;
}

corebluetoothperipheraldevice* corebluetoothcentralplugin::find_device(CBPeripheral* peripheral)
{
    std::string identifier_str( [[[peripheral identifier] UUIDString] UTF8String] );
    for( std::vector<device*>::iterator it = devices_.begin(); it != devices_.end(); ++it )
    {
        if( (*it)->addr() == identifier_str )
        {
            return (corebluetoothperipheraldevice*)(*it);
        }
    }
    return NULL;
}

