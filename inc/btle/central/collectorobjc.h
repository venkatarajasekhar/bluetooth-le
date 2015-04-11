
#ifndef btle_collectorobjc_h
#define btle_collectorobjc_h

#import <Foundation/Foundation.h>
#include "btle/central/collector.h"

using namespace btle;
using namespace btle::central;

class collectorobjcimpl;

@protocol collectorobjc_delegate;

@interface collectorobjc : NSObject
{
@package
    id<collectorobjc_delegate> delegate_;
@public
    collectorobjcimpl* collector_;
}

- (instancetype)initWithDelegate:(id<collectorobjc_delegate>)delegate;

@end

@protocol collectorobjc_delegate <NSObject>

-(void) device_discovered:(device&) dev;
-(void) device_service_value_updated:(device&) dev srv: (const gatt_services::gattservicebase*) srv;
-(void) device_service_value_updated:(device&) dev srv: (const service&) srv chr: (const characteristic&) chr data: (const std::string&) data;
-(void) device_characteristic_read:(device&) dev srv: (const service&) srv chrs: (const characteristic&) chrs data: (const std::string&) data err: (const error&) err;
-(void) device_state_changed:(device&) dev;
-(void) device_gatt_service_discovered:(device&) dev srv: (const gatt_services::gattservicebase*) srv;
-(void) device_service_discovery_failed:(device&) dev services: (const service_list&) services err: (const error&) err;
-(void) device_characteristic_discovery_failed:(device&) dev srv: (const service&) srv chrs: (const chr_list&) chrs err: (const error&) err;

@end

#endif
