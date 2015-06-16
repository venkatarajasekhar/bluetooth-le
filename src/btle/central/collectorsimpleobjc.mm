
#include "btle/central/collectorsimpleobjc.h"
#include "btle/gatt_services/hrservice.h"
#include "btle/gatt_services/rscservice.h"
#include "btle/gatt_services/cscservice.h"

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
    
    void new_device_discovered_cb(device& dev)
    {
        [objc_->delegate_ new_device_discovered:DEV_ADDR_TO_NSSTRING(dev)
                                           name:DEV_NAME_TO_NSSTRING(dev)];
    }
    
    void device_discovered_cb(device& dev)
    {
        [objc_->delegate_ device_discovered:DEV_ADDR_TO_NSSTRING(dev)
                                       name:DEV_NAME_TO_NSSTRING(dev)
                                       state:[NSString stringWithUTF8String:dev.state_string().c_str()]
                                       rssi:dev.rssi_filter().mean_median()];
    }
    
    void device_service_value_updated_cb(device& dev, const gatt_services::gattservicebase* srv)
    {
        NSString* service_string = [NSString stringWithUTF8String:srv->service_uuid().to_string().c_str()];
        NSString* dev_addr = DEV_ADDR_TO_NSSTRING(dev);
        NSString* dev_name = DEV_NAME_TO_NSSTRING(dev);
        NSString* srv_json = @"";//[NSString stringWithUTF8String:srv->json(uuid(HEART_RATE_MEASUREMENT)).c_str()];
        [objc_->delegate_ device_service_value_updated:dev_addr
                                                  name:dev_name
                                                   srv:service_string
                                                  json:srv_json];
        switch (srv->service_uuid().uuid16bit()) {
            case HEART_RATE_SERVICE:
            {
                const hrservice* hr = (const hrservice*)srv;
                NSMutableArray* rrs = [[NSMutableArray alloc] initWithCapacity:hr->rr_values().size()];
                for( std::vector<int>::const_iterator it = hr->rr_values().begin(); it != hr->rr_values().end(); ++it )
                {
                    [rrs addObject:[[NSNumber alloc] initWithInt:*it]];
                }
                [objc_->delegate_ device_hr_value_updated:DEV_ADDR_TO_NSSTRING(dev)
                                                     name:DEV_NAME_TO_NSSTRING(dev)
                                                       hr:hr->hr_value()
                                                  contact:hr->sensor_contact()
                                                      rrs:rrs
                                                   energy:hr->energy_expeneded()];
                break;
            }
            case RSC_SERVICE:
            {
                const rscservice* rsc = (const rscservice*)srv;
                [objc_->delegate_ device_rsc_value_updated:DEV_ADDR_TO_NSSTRING(dev)
                                                      name:DEV_NAME_TO_NSSTRING(dev)
                                                     speed:rsc->speed()
                                                   walking:rsc->is_walking()
                                              strideLength:rsc->stride_length()
                                                  distance:rsc->distance()];
                break;
            }
            case CSC_SERVICE:
            {
                const cscservice* csc = (const cscservice*)srv;
                [objc_->delegate_ device_csc_value_updated:DEV_ADDR_TO_NSSTRING(dev)
                                                      name:DEV_NAME_TO_NSSTRING(dev)
                                                     speed:csc->speed()
                                                   cadence:csc->cadence()
                                             speed_present:csc->is_speed_present()
                                           cadence_present:csc->is_cadence_present()];
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
    
    void plugin_state_changed_cb(plugin_state state)
    {
        [objc_->delegate_ plugin_state_changed:state];
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

-(void) dealloc
{
    collector_->stop();
    delete collector_;
}

-(void) connect_device:(NSString *)addr
{
    collector_->connect_device(bda([addr UTF8String]));
}

-(void) disconnect_device:(NSString *)addr
{
    collector_->disconnect_device(bda([addr UTF8String]));
}

- (void) scan_devices
{
    collector_->start_scan();
}

- (void) stop_scan_devices
{
    collector_->stop_scan();
}

@end
