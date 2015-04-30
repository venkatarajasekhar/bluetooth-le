//
//  ViewController.m
//  btle_test
//
//  Created by Erkki  on 03/04/15.
//  Copyright (c) 2015 Erkki Silvola. All rights reserved.
//

#import "ViewController.h"

#include "btle_core.h"

class btletest: public collector
{
    void device_discovered_cb(device& dev)
    {
        NSLog(@"Device discovered!! rssi: %f",dev.rssi_filter().mean_median());
        
        if( dev.state() == DEVICE_DISCONNECTED )
        {
            connect_device(dev);
        }
    }
    
    void device_service_value_updated_cb(device& dev, const gatt_services::gattservicebase* srv)
    {
        if( srv->service_uuid() == HEART_RATE_SERVICE ){
            NSLog( @"HR: %i", ((hrservice*)srv)->hr_value() );
        }
    }
    
    void device_service_value_updated_cb(device& dev, const service& srv, const characteristic& chr, const std::string& data)
    {
        
    }
    
    void device_characteristic_read_cb(device& dev, const service& srv, const characteristic& chrs, const std::string& data, const error& err)
    {
        
    }
    
    void device_state_changed_cb(device& dev)
    {
        NSLog(@"State: %s", dev.state_string().c_str());
    }
};

@interface ViewController ()
{
    btletest* test;
}
@end

@implementation ViewController

@synthesize simple_;

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    btle::log::instance().set_options(btle::LOG_PRINT);
    
    simple_ = [[collectorsimpleobjc alloc] initWithDelegate:self];
    [simple_ scan_devices];
    
    /*test = new btletest;
    test->auto_start();
    uuid_list list;
    list.push_back(uuid(HEART_RATE_SERVICE));
    test->add_scan_filter(new btle::uuidscanfilter(list));
    test->start_scan();*/
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void) device_discovered:(NSString*) addr name: (NSString*) name state:(NSString*) state rssi: (int) rssi
{
    NSLog(@"addr: %@ name: %@ rssi: %i", addr, name, rssi);
    
    if([state compare:@"DEVICE_DISCONNECTED"] == NSOrderedSame)
    {
        [simple_ connect_device:addr];
    }
}

-(void) device_service_value_updated:(NSString*) addr name: (NSString*) name srv: (NSString*) srv json:(NSString*) json
{
    NSLog(@"addr: %@ name: %@ srv: %@ ", addr, name, srv);
}

-(void) device_hr_value_updated:(NSString *)addr name:(NSString *)name hr:(int)hr contact:(bool)contact rrs:(NSMutableArray *)rrs energy:(int)energy
{
    NSLog(@"HR: %i contact: %i", hr, contact);
}

-(void) device_rsc_value_updated:(NSString *)addr name:(NSString *)name speed:(double)speed walking:(bool)walking strideLength:(int)strideLength distance:(double)distance
{
    
}

-(void) device_characteristic_read:(NSString*) addr name: (NSString*) name srv: (NSString*) srv chr: (NSString*) chr data: (NSString*) data err: (int) err
{
    NSLog(@"addr: %@ name: %@ srv: %@ chr: %@ data: %@", addr, name, srv, chr, data);
}

-(void) device_state_changed:(NSString*) addr name: (NSString*) name state: (NSString*) state
{
    NSLog(@"addr: %@ name: %@ state: %@", addr, name, state);
}

-(void) plugin_state_changed:(btle::central::central_plugin_state) state
{
    NSLog(@"state: %i",state);
}

@end
