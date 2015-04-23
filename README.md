# bluetooth-le
C++ bluetooth le library

There is two main purposes where this library is intended for.
1. To provide easy to use interface to receive sensor Heart rate etc..., the library offers a set of apis to use low level, medium level and high level api
2. To provide easy to use data transfer link between two devices, without client to consern about attribute protocol max payload etc...

The library is allso highly configurable, for scanning filtering there is a simple abstract interface which needs to be implemented
for new gatt service implementation see Heart rate service for exsample

Note for ios users you need to add "Other linker flags" --> -all_load

Goals:

Version 1.x.x : First "Beta" version, only ios/mac xcode/qt support (sorry no linux support for the first version) 
Version 2.x.x : Core functionality should be stable, linux support (and maybe windows too), 
Version 3.x.x : 

simple example in ios using high level Api:

// HEADER START

@interface ViewController : UIViewController<collectorsimpleobjc_delegate>

@property (nonatomic) collectorsimpleobjc* simple_;

@end

// HEADER END

// *.m

@interface ViewController ()
{
    btletest* test;
}
@end

@implementation ViewController

@synthesize simple_;

- (void)viewDidLoad {
    [super viewDidLoad];

    // enable logging
    btle::log::instance().set_options(btle::LOG_PRINT);

    simple_ = [[collectorsimpleobjc alloc] initWithDelegate:self];
    [simple_ scan_devices];
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

