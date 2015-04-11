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

@end

@protocol collectorsimpleobjc_delegate <NSObject>

@required
-(void) device_discovered:(NSString*) addr name: (NSString*) name rssi: (int) rssi;
-(void) device_service_value_updated:(NSString*) addr name: (NSString*) name srv: (NSString*) srv value: (double) value json:(NSString*) json;
-(void) device_characteristic_read:(NSString*) addr name: (NSString*) name srv: (NSString*) srv chr: (NSString*) chr data: (NSString*) data err: (int) err;
-(void) device_state_changed:(NSString*) addr name: (NSString*) name state: (NSString*) state;

@end
