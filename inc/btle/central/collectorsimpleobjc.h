//
//  collectorsimpleobjc.h
//  btle
//
//  Created by Erkki  on 11/04/15.
//  Copyright (c) 2015 Erkki Silvola. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "btle/central/collector.h"

using namespace btle;
using namespace btle::central;

class collectorsimpleobjcimpl;

@protocol collectorsimpleobjc_delegate;

@interface collectorsimpleobjc : NSObject
{
@package
    id<collectorsimpleobjc_delegate> delegate_;
@public
    collectorsimpleobjcimpl* collector_;
}

- (instancetype)initWithDelegate:(id<collectorsimpleobjc_delegate>)delegate;
- (void) connect_device:(NSString*) addr;
- (void) disconnect_device:(NSString*) addr;
- (void) scan_devices;
- (void) stop_scan_devices;

@end

@protocol collectorsimpleobjc_delegate <NSObject>

@required

-(void) plugin_state_changed:(btle::central::central_plugin_state) state;
-(void) device_discovered:(NSString*) addr name: (NSString*) name state:(NSString*) state rssi: (int) rssi;
-(void) device_service_value_updated:(NSString*) addr name: (NSString*) name srv: (NSString*) srv json:(NSString*) json;
-(void) device_hr_value_updated:(NSString*) addr name: (NSString*) name hr: (int) hr contact: (bool) contact rrs: (NSMutableArray*) rrs energy: (int) energy;
-(void) device_rsc_value_updated:(NSString*) addr name: (NSString*) name speed: (double) speed walking: (bool) walking strideLength: (int) strideLength distance: (double) distance;
-(void) device_characteristic_read:(NSString*) addr name: (NSString*) name srv: (NSString*) srv chr: (NSString*) chr data: (NSString*) data err: (int) err;
-(void) device_state_changed:(NSString*) addr name: (NSString*) name state: (NSString*) state;

@end
