
#include "peripheral/apple/corebluetoothperipheralplugin.h"
#include "peripheral/peripheralpluginregisterer.h"
#include "btle/error.h"
#include "btle/characteristic.h"
#include "btle/service.h"
#include "btle/attributerequest.h"


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
                                     (long int)chr,
                                     &srv);
            
            if( btle_chr.properties() & GATT_NOTIFY ||
                btle_chr.properties() & GATT_INDICATE ){
                btle_chr << btle::descriptor(CLIENT_CHARACTERISTIC_CONFIGURATION,&btle_chr);
            }
            if( btle_chr.properties() & GATT_BROADCAST ){
                btle_chr << btle::descriptor(SERVER_CHARACTERISTIC_CONFIGURATION,&btle_chr);
            }
            
            srv << btle_chr;
        }
        
        return srv;
    }
    
    
    inline btle::characteristic* btle_chr_to_cbcharacteristic(btle::service& srv,CBCharacteristic* chr){
        btle::characteristic* chr_btle=NULL;
        for(chr_iterator it = srv.characteristics().begin(); it != srv.characteristics().end(); ++it){
            if( it->instance_id() == (long int)chr)
            {
                chr_btle = (btle::characteristic*)&(*it);
                break;
            }
        }
        return chr_btle;
    }
    
    inline btle::descriptor* cbcharacteristic_to_desc(btle::characteristic* chr_btle, CBCharacteristic* chr){
        btle::descriptor* ret=NULL;
        for( std::vector<btle::descriptor>::iterator it = chr_btle->descriptors().begin(); it != chr_btle->descriptors().end(); ++it )
        {
            if(it->type() == CLIENT_CHARACTERISTIC_CONFIGURATION)
            {
                // TODO FIXME
                 ret = (btle::descriptor*)&(*it);
                break;
            }
        }
        return ret;
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
    corebluetoothperipheralplugin* parent = (corebluetoothperipheralplugin*)parent_;
    switch ([peripheral state]) {
        case CBPeripheralManagerStatePoweredOff:
        {
            break;
        }
        case CBPeripheralManagerStateUnknown:
        {
            break;
        }
        case CBPeripheralManagerStateResetting:
        {
            break;
            
        }
        case CBPeripheralManagerStateUnsupported:
        {
            break;
            
        }
        case CBPeripheralManagerStateUnauthorized:
        {
            
            break;
        }
        case CBPeripheralManagerStatePoweredOn:
        {
            break;
        }
        default:
            break;
    }
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
    btle::service srv = btle_service_from_cbservice(characteristic.service);
    btle::characteristic* chr = btle_chr_to_cbcharacteristic(srv,characteristic);
    btle::descriptor* desc = cbcharacteristic_to_desc(chr, characteristic);
    desc->set_notifying(true);
    ((corebluetoothperipheralplugin*)parent_)->observer_.descriptor_written(*((corebluetoothperipheralplugin*)parent_)->central_, srv, *chr,*desc);
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral central:(CBCentral *)central didUnsubscribeFromCharacteristic:(CBCharacteristic *)characteristic
{
    btle::service srv = btle_service_from_cbservice(characteristic.service);
    btle::characteristic* chr = btle_chr_to_cbcharacteristic(srv,characteristic);
    btle::descriptor* desc = cbcharacteristic_to_desc(chr, characteristic);
    desc->set_notifying(true);
    ((corebluetoothperipheralplugin*)parent_)->observer_.descriptor_written(*((corebluetoothperipheralplugin*)parent_)->central_, srv, *chr,*desc);
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral didReceiveReadRequest:(CBATTRequest *)request
{
    btle::service srv = btle_service_from_cbservice(request.characteristic.service);
    btle::characteristic* chr = btle_chr_to_cbcharacteristic(srv,request.characteristic);
    attributerequest req = ((corebluetoothperipheralplugin*)parent_)->observer_.characteristic_read(*((corebluetoothperipheralplugin*)parent_)->central_, srv, *chr);
    [request setValue:[NSData dataWithBytes:req.string_value().c_str() length:req.string_value().size()]];
    // TODO implement btle error to CB error translator
    [peripheral respondToRequest:request withResult:(CBATTError)req.err().code()];
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral didReceiveWriteRequests:(NSArray *)requests
{
    for( CBATTRequest* request in requests )
    {
        btle::service srv = btle_service_from_cbservice(request.characteristic.service);
        btle::characteristic* chr = btle_chr_to_cbcharacteristic(srv,request.characteristic);
        std::string data((const char*)[[request value] bytes],[[request value] length]);
        ((corebluetoothperipheralplugin*)parent_)->observer_.characteristic_write(*((corebluetoothperipheralplugin*)parent_)->central_, srv, *chr, data);

    }
}

- (void)peripheralManagerIsReadyToUpdateSubscribers:(CBPeripheralManager *)peripheral
{
    ((corebluetoothperipheralplugin*)parent_)->observer_.notify_channel_free(*((corebluetoothperipheralplugin*)parent_)->central_);
}

@end

corebluetoothperipheralplugin::corebluetoothperipheralplugin(peripheralpluginobserver& observer)
: peripheralplugininterface(observer),
  central_(NULL)
{
}

unsigned int corebluetoothperipheralplugin::features()
{
    // corebluetooth has no extras
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
