
#include "btle/central/apple/corebluetoothperipheraldevice.h"

using namespace btle::central::apple;

namespace {
    #define UUID_2_STRING(a) std::string([ [ [a UUID] UUIDString] UTF8String])
}

corebluetoothperipheraldevice::corebluetoothperipheraldevice(const bda& addr)
: device(addr)
{
}

corebluetoothperipheraldevice::~corebluetoothperipheraldevice()
{
}

void corebluetoothperipheraldevice::process_adv_data()
{
    
}

void corebluetoothperipheraldevice::process_services_discovered(CBPeripheral* peripheral, btle::service_list& list)
{
    for( CBService* service in [peripheral services] )
    {
        btle::service srv((uuid(UUID_2_STRING(service))),
                          (long int)service);
        list.push_back(srv);
    }
}

btle::service* corebluetoothperipheraldevice::process_characteristics_discovered(CBService* service)
{
    btle::service* ret = NULL;
    for( service_iterator it_s = db_.services().begin(); it_s != db_.services().end(); ++it_s )
    {
        if( it_s->instance_id() == (long int)service )
        {
            ret = (btle::service*)&(*it_s);
            for( CBCharacteristic* characteristic in [service characteristics] )
            {
                btle::characteristic chr((uuid(UUID_2_STRING(characteristic))),
                                         [characteristic properties],
                                         (long int)characteristic);
                
                if( chr.properties() & GATT_NOTIFY ||
                    chr.properties() & GATT_INDICATE ){
                    chr << btle::descriptor(CLIENT_CHARACTERISTIC_CONFIGURATION);
                }
                if( chr.properties() & GATT_BROADCAST ){
                    chr << btle::descriptor(SERVER_CHARACTERISTIC_CONFIGURATION);
                }
                (*it_s) << chr;
            }
            return ret;
        }
    }
    return ret;
}

void corebluetoothperipheraldevice::fetch_service_and_characteristic(CBCharacteristic* aChr,btle::service*& service, btle::characteristic*& chr)
{
    for( service_iterator it_s = db_.services().begin(); it_s != db_.services().end(); ++it_s )
    {
        if( it_s->instance_id() == (long int)aChr.service )
        {
            for( chr_iterator it_c = it_s->characteristics().begin(); it_c != it_s->characteristics().end(); ++it_c )
            {
                if( it_c->instance_id() == (long int)aChr )
                {
                    chr = (btle::characteristic*)&(*it_c);
                    service = (btle::service*)&(*it_s);
                    return;
                }
            }
        }
    }
}

void corebluetoothperipheraldevice::fetch_service_and_characteristic(CBDescriptor* aDesc,btle::service*& service, btle::characteristic*& chr)
{
    for( service_iterator it_s = db_.services().begin(); it_s != db_.services().end(); ++it_s )
    {
        if( it_s->instance_id() == (long int)aDesc.characteristic.service )
        {
            for( chr_iterator it_c = it_s->characteristics().begin(); it_c != it_s->characteristics().end(); ++it_c )
            {
                if( it_c->instance_id() == (long int)aDesc.characteristic )
                {
                    chr = (btle::characteristic*)&(*it_c);
                    service = (btle::service*)&(*it_s);
                    return;
                }
            }
        }
    }
}

CBService* corebluetoothperipheraldevice::fetch_service(const btle::service& srv)
{
    for( CBService* service in [peripheral_ services] )
    {
        if( (long int)service == srv.instance_id() )
        {
            return service;
        }
    }
    return NULL;
}

CBCharacteristic* corebluetoothperipheraldevice::fetch_characteristic(const btle::characteristic& chr)
{
    for( CBService* service in [peripheral_ services] )
    {
        for( CBCharacteristic* aChr in [service characteristics] )
        {
            if( (long int)aChr == chr.instance_id() )
            {
                return aChr;
            }
        }
    }
    return NULL;
}

CBCharacteristic* corebluetoothperipheraldevice::fetch_characteristic(const btle::uuid& uid)
{
    for( CBService* service in [peripheral_ services] )
    {
        for( CBCharacteristic* aChr in [service characteristics] )
        {
            if( uid == btle::uuid(UUID_2_STRING(aChr)) )
            {
                return aChr;
            }
        }
    }
    return NULL;
}
