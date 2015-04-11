
#include "btle/central/collectorsimpleobjc.h"
#include "btle/gatt_services/hrservice.h"
#include "btle/gatt_services/rscservice.h"

using namespace btle::gatt_services;

namespace {
    #define DEV_ADDR_TO_NSSTRING(a) [NSString stringWithUTF8String:a.addr().to_string().c_str()]
    #define DEV_NAME_TO_NSSTRING(a) [NSString stringWithUTF8String:a.name().c_str()]
    #define DEV_BASE_TO_NSSTRING(a) [NSString stringWithUTF8String:a.to_string().c_str()]
}

class collectorsimpleobjcimpl: public collector
{
private:
    collectorsimpleobjc* objc_;
    
public:
    
    collectorsimpleobjcimpl(collectorsimpleobjc* objc)
    : objc_(objc)
    {
    }
    
    void device_discovered_cb(device& dev)
    {
        [objc_->delegate_ device_discovered:DEV_ADDR_TO_NSSTRING(dev)
                                       name:DEV_NAME_TO_NSSTRING(dev)
                                       rssi:dev.rssi_filter().mean_median()];
    }
    
    void device_service_value_updated_cb(device& dev, const gatt_services::gattservicebase* srv)
    {
        NSString* service_string = [NSString stringWithUTF8String:srv->service_uuid().to_string().c_str()];
        switch (srv->service_uuid().uuid16bit()) {
            case HEART_RATE_SERVICE:
            {
                const hrservice* hr = (const hrservice*)srv;
                [objc_->delegate_ device_service_value_updated:DEV_ADDR_TO_NSSTRING(dev)
                                                          name:DEV_NAME_TO_NSSTRING(dev)
                                                           srv:service_string
                                                         value:(double)hr->hr_value()
                             json:[NSString stringWithUTF8String:srv->json(uuid(HEART_RATE_MEASUREMENT)).c_str()]];
                break;
            }
            default:
                break;
        }
    }
    
    void device_service_value_updated_cb(device& dev, const service& srv, const characteristic& chr, const std::string& data)
    {
    }
    
    void device_characteristic_read_cb(device& dev, const service& srv, const characteristic& chrs, const std::string& data, const error& err)
    {
        [objc_->delegate_ device_characteristic_read:DEV_ADDR_TO_NSSTRING(dev)
                                                name:DEV_NAME_TO_NSSTRING(dev)
                                                 srv:DEV_BASE_TO_NSSTRING(srv)
                                                 chr:DEV_BASE_TO_NSSTRING(chrs)
                                                data:[NSString stringWithUTF8String:data.c_str()]
                                                 err:err.code()];
    }
    
    void device_state_changed_cb(device& dev)
    {
       [objc_->delegate_ device_state_changed:DEV_ADDR_TO_NSSTRING(dev)
                                         name:DEV_NAME_TO_NSSTRING(dev)
                                        state:[NSString stringWithUTF8String:dev.state_string().c_str()]];
    }
    
    void device_gatt_service_discovered_cb(device& dev, const gatt_services::gattservicebase *srv)
    {
    }
    
    void device_service_discovery_failed_cb(device& dev, const service_list& services, const error& err)
    {
    }
    
    void device_characteristic_discovery_failed_cb(device& dev, const service& srv, const chr_list& chrs, const error& err)
    {
    }
};

@implementation collectorsimpleobjc

- (instancetype)initWithDelegate:(id<collectorsimpleobjc_delegate>)delegate
{
    self = [super init];
    if (self)
    {
        collector_ = new collectorsimpleobjcimpl(self);
        // TODO, ok or not to auto start?
        (void)collector_->auto_start();
        delegate_ = delegate;
    }
    return self;
}

-(void) connect_device:(NSString *)addr
{
    collector_->connect_device(bda([addr UTF8String]));
}

-(void) disconnect_device:(NSString *)addr
{
    collector_->disconnect_device(bda([addr UTF8String]));
}

@end
