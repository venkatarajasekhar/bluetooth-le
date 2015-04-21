
#include "btle/timer.h"
#include "btle/log.h"

#import <Foundation/Foundation.h>

using namespace btle;

@interface timer_darwin_private : NSObject
{
    @public
        timer* timer_;
        NSTimer* ntimer_;
        timercallback* callback_;
}

-(id) init:(timer*) parent;
-(void) start:(int) ms cb: (timercallback*) cb;
-(void) stop;

@end

@implementation timer_darwin_private

-(id) init:(timer*) parent
{
    self = [super init];
    if( self )
    {
        self->timer_ = parent;
    }
    return self;
}

-(void) callback
{
    callback_->timer_expired(timer_);
}

-(void) start:(int) ms cb: (timercallback*) cb
{
    callback_ = cb;
    [self stop];
    ntimer_ = [NSTimer scheduledTimerWithTimeInterval:(double)ms/1000.0
                                               target:self
                                             selector:@selector(callback)
                                             userInfo:nil
                                              repeats:NO];
}

-(void) stop
{
    if(ntimer_)
    {
        [ntimer_ invalidate];
        ntimer_ = nil;
    }
}

@end

namespace {
}

timer::timer()
: object_(NULL)
{
    timer_darwin_private* pobject = [[timer_darwin_private alloc] init:this];
    object_ = (void*)CFBridgingRetain(pobject);
}

timer::~timer()
{
    // TODO
}

void timer::start(int ms, timercallback* callback)
{
    [((__bridge timer_darwin_private*)object_) start:ms cb:callback];
}

void timer::stop()
{
    [((__bridge timer_darwin_private*)object_) stop];
}
