
#import <Foundation/Foundation.h>
#include "btle/peripheral/peripheral.h"

using namespace btle;
using namespace btle::peripheral;

@protocol peripheralsimpleobjc_delegate;

@interface peripheralsimpleobjc : NSObject
{
@package
    id<peripheralsimpleobjc_delegate> delegate_;
}

-(instancetype) initWithDelegate:(id<peripheralsimpleobjc_delegate>) delegate;
-(void) write_file:(NSString*) centralAddr data: (NSString*) data identifier:(int) identifier;

@end

@protocol peripheralsimpleobjc_delegate <NSObject>

@required

-(void) plugin_state_changed:(btle::plugin_state) state;
-(void) btle_ftp_in_progress:(NSString*) centralAddr progress:(double) progress data:(NSString*) data identifier:(int) identifier;
-(void) btle_ftp_out_progress:(NSString*) centralAddr progress:(double) progress identifier:(int) identifier;
-(void) central_connected:(NSString*) centralAddr;
-(void) central_disconnected:(NSString*) centralAddr;

@end
