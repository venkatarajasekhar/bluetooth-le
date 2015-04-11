
#include "btle/central/collectorobjc.h"

class collectorobjcimpl: public collector
{
private:
    collectorobjc* objc_;

public:
    
    collectorobjcimpl(collectorobjc* objc)
    : objc_(objc)
    {
    }
    
    void device_discovered_cb(device& dev)
    {
        [objc_->delegate_ device_discovered:dev];
    }
    
    void device_service_value_updated_cb(device& dev, const gatt_services::gattservicebase* srv)
    {
        [objc_->delegate_ device_service_value_updated:dev srv:srv];
    }
    
    void device_service_value_updated_cb(device& dev, const service& srv, const characteristic& chr, const std::string& data)
    {
        [objc_->delegate_ device_service_value_updated:dev srv:srv chr:chr data:data];
    }
    
    void device_characteristic_read_cb(device& dev, const service& srv, const characteristic& chrs, const std::string& data, const error& err)
    {
        [objc_->delegate_ device_characteristic_read:dev srv:srv chrs:chrs data:data err:err];
    }
    
    void device_state_changed_cb(device& dev)
    {
        [objc_->delegate_ device_state_changed:dev];
    }
    
    void device_gatt_service_discovered_cb(device& dev, const gatt_services::gattservicebase *srv)
    {
        [objc_->delegate_ device_gatt_service_discovered:dev srv:srv];
    }
    
    void device_service_discovery_failed_cb(device& dev, const service_list& services, const error& err)
    {
        [objc_->delegate_ device_service_discovery_failed:dev services:services err:err];
    }
    
    void device_characteristic_discovery_failed_cb(device& dev, const service& srv, const chr_list& chrs, const error& err)
    {
        [objc_->delegate_ device_characteristic_discovery_failed:dev srv:srv chrs:chrs err:err];
    }
};

@implementation collectorobjc

- (instancetype)initWithDelegate:(id<collectorobjc_delegate>)delegate
{
    self = [super init];
    if (self)
    {
        collector_ = new collectorobjcimpl(self);
        delegate_ = delegate;
    }
    return self;
}

@end

