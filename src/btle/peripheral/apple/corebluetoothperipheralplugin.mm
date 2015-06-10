
#include "peripheral/apple/corebluetoothperipheralplugin.h"
#include "peripheral/peripheralpluginregisterer.h"
#include "btle/error.h"
#include "btle/characteristic.h"
#include "btle/service.h"


using namespace btle;
using namespace btle::peripheral;
using namespace btle::peripheral::apple;

namespace {
    peripheralpluginregisterer<corebluetoothperipheralplugin> registration;
    
    #define UUID_2_STRING(a) std::string([ [ [a UUID] UUIDString] UTF8String])
    
    inline btle::error btle_error_from_nserror(NSError* error)
    {
        return btle::error( error ? (int)[error code] : 0, error ? "Unknown CoreBluetooth Error" : "");
    }
    
    inline btle::service btle_service_from_cbservice(CBService* service)
    {
        btle::service srv(uuid(UUID_2_STRING(service)),
                          (long int)service);
        for( CBCharacteristic* chr in [service characteristics])
        {
            btle::characteristic btle_chr((uuid(UUID_2_STRING(chr))),
                                     [chr properties],
                                     (long int)chr);
            srv << btle_chr;
        }
        
        return srv;
    }
}

@implementation corebluetoothperipheralpluginprivate

-(id) init:(corebluetoothperipheralplugin*) plugin
{
    self = [super init];
    if(self)
    {
        parent_ = plugin;
        manager_ = [[CBPeripheralManager alloc] initWithDelegate:self queue:nil];
    }
    return self;
}

-(void) dealloc
{
}

- (void)peripheralManagerDidUpdateState:(CBPeripheralManager *)peripheral
{
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral willRestoreState:(NSDictionary *)dict
{
    // TODO
}

- (void)peripheralManagerDidStartAdvertising:(CBPeripheralManager *)peripheral error:(NSError *)error
{
    btle::error err = btle_error_from_nserror(error);
    ((corebluetoothperipheralplugin*)parent_)->observer_.advertising_started(err);
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral didAddService:(CBService *)service error:(NSError *)error
{
    btle::error err = btle_error_from_nserror(error);
    btle::service srv = btle_service_from_cbservice(service);
    ((corebluetoothperipheralplugin*)parent_)->observer_.service_added(srv, err);
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral central:(CBCentral *)central didSubscribeToCharacteristic:(CBCharacteristic *)characteristic
{
    
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral central:(CBCentral *)central didUnsubscribeFromCharacteristic:(CBCharacteristic *)characteristic
{

}

- (void)peripheralManager:(CBPeripheralManager *)peripheral didReceiveReadRequest:(CBATTRequest *)request
{

}

- (void)peripheralManager:(CBPeripheralManager *)peripheral didReceiveWriteRequests:(NSArray *)requests
{

}

- (void)peripheralManagerIsReadyToUpdateSubscribers:(CBPeripheralManager *)peripheral
{

}

@end

corebluetoothperipheralplugin::corebluetoothperipheralplugin(peripheralpluginobserver& observer)
: peripheralplugininterface(observer)
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

void corebluetoothperipheralplugin::start()
{
    peripheral_ = [[corebluetoothperipheralpluginprivate alloc] init: this];
}

void corebluetoothperipheralplugin::stop()
{
    #ifdef DESKTOP_BUILD
    [peripheral_ dealloc];
    #endif
    peripheral_ = nil;
}

peripheralplugininterface& corebluetoothperipheralplugin::operator << (const service& srv)
{
    
    return *this;
}

void corebluetoothperipheralplugin::start_advertising(int ms,const adv_fields& fields)
{
    stop_advertising();
    NSMutableDictionary* advFields = [[NSMutableDictionary alloc] init];
    for(adv_fields::const_iterator it = fields.begin(); it != fields.end(); ++it)
    {
        switch (it->first)
        {
            case GAP_ADTYPE_LOCAL_NAME_COMPLETE:
            case GAP_ADTYPE_LOCAL_NAME_SHORT:
            {
                [advFields setObject:[NSString stringWithUTF8String:it->second.string_value().c_str()] forKey:CBAdvertisementDataLocalNameKey];
                break;
            }
            case GAP_ADTYPE_16BIT_MORE:
            case GAP_ADTYPE_16BIT_COMPLETE:
            {
                [advFields setObject:[CBUUID UUIDWithString:[NSString stringWithUTF8String:it->second.to_string().c_str()]] forKey:CBAdvertisementDataServiceUUIDsKey];
                break;
            }
            case GAP_ADTYPE_128BIT_MORE:
            case GAP_ADTYPE_128BIT_COMPLETE:
            {
                [advFields setObject:[CBUUID UUIDWithData:[NSData dataWithBytes:it->second.string_value().c_str() length:it->second.string_value().size()]] forKey:CBAdvertisementDataServiceUUIDsKey];
                break;
            }
            default:
                break;
        }
    }
    [peripheral_->manager_ startAdvertising:advFields];
}

void corebluetoothperipheralplugin::stop_advertising()
{
    [peripheral_->manager_ stopAdvertising];
}

std::vector<advertisement_data_type> corebluetoothperipheralplugin::supported_adtypes()
{
    std::vector<advertisement_data_type> types;
    types.push_back(advertisement_data_type::GAP_ADTYPE_LOCAL_NAME_COMPLETE);
    types.push_back(advertisement_data_type::GAP_ADTYPE_LOCAL_NAME_SHORT);
    types.push_back(advertisement_data_type::GAP_ADTYPE_16BIT_COMPLETE);
    types.push_back(advertisement_data_type::GAP_ADTYPE_16BIT_MORE);
    types.push_back(advertisement_data_type::GAP_ADTYPE_128BIT_COMPLETE);
    types.push_back(advertisement_data_type::GAP_ADTYPE_128BIT_MORE);
    
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
