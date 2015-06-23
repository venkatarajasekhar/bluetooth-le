
#import <Foundation/Foundation.h>
#include "btle/peripheral/peripheral.h"

using namespace btle;
using namespace btle::peripheral;

class peripheralobjcimpl;

@protocol peripheralobjc_delegate;

@interface peripheralobjc : NSObject
{
@package
    id<peripheralobjc_delegate> delegate_;
@public
    peripheralobjcimpl* peripheral_;
}

-(instancetype) initWithDelegate:(id<peripheralobjc_delegate>) delegate;

@end

@protocol peripheralobjc_delegate <NSObject>

@required

-(void) plugin_state_changed:(btle::plugin_state) state;
-(void) btle_ftp_in_progress:(device&) dev progress:(double) progress data:(const std::string&) data identifier:(int) identifier;
-(void) btle_ftp_out_progress:(device&) dev progress:(double) progress identifier:(int) identifier;
-(void) advertising_started:(error&) err;
-(void) advertising_stopped;
-(void) service_added:(service&) srv err:(const error&) err;
-(void) central_connected:(device&) dev;
-(void) central_disconnected:(device&) dev;
-(void) descriptor_written:(device&) central srv:(const service&) srv chr:(const characteristic&) chr desc:(const descriptor&) desc;
-(btle::attributerequest) characteristic_read:(device&) central srv:(const service&) srv chr:(const characteristic&) chr;
-(void) characteristic_write:(device&) central srv:(const service&) srv chr:(const characteristic&) chr data:(const std::string&) data;

@end

