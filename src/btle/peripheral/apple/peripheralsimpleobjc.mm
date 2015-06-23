
#include "btle/peripheral/peripheralsimpleobjc.h"
#include "btle/log.h"
#include <stdexcept>

namespace {
    #define DEV_ADDR_TO_NSSTRING(a) [NSString stringWithUTF8String:a.addr().to_string().c_str()]
    #define DEV_NAME_TO_NSSTRING(a) [NSString stringWithUTF8String:a.name().c_str()]
    #define DEV_BASE_TO_NSSTRING(a) [NSString stringWithUTF8String:a.to_string().c_str()]
}

class peripheralsimpleobjcimpl: public btle::peripheral::peripheral
{
private:
    peripheralsimpleobjc* peripheral_;
public:
    
    peripheralsimpleobjcimpl(peripheralsimpleobjc* peripheral)
    : peripheral_(peripheral)
    {
    }
    
    void btle_ftp_in_progress_cb(device& dev, double progress, const std::string& data, int identifier)
    {
        [peripheral_->delegate_ btle_ftp_in_progress:DEV_ADDR_TO_NSSTRING(dev) progress:progress data:[NSString stringWithUTF8String:data.c_str()] identifier:identifier];
    }
    
    void btle_ftp_out_progress_cb(device& dev, double progress, int identifier)
    {
        [peripheral_->delegate_ btle_ftp_out_progress:DEV_ADDR_TO_NSSTRING(dev) progress:progress identifier:identifier];
    }
    
    void plugin_state_changed_cb(plugin_state state)
    {
        [peripheral_->delegate_ plugin_state_changed:state];
    }
    
    void advertising_started_cb(error& err)
    {
    }
    
    void advertising_stopped_cb()
    {
    }
    
    void service_added_cb(service& srv, const error& err)
    {
    
    }
    
    void central_connected_cb(device& dev)
    {
    }
    
    void central_disconnected_cb(device& dev)
    {
    }
    
    void descriptor_written_cb(device& central, const service& srv, const characteristic& chr, const descriptor& desc)
    {
    }
    
    btle::attributerequest characteristic_read_cb(device& central, const service& srv, const characteristic& chr)
    {
        return btle::attributerequest();
    }
    
    void characteristic_write_cb(device& central,const service& srv,const characteristic& chr,const std::string& data)
    {
    }
};

@interface peripheralsimpleobjc()
{
    peripheralsimpleobjcimpl* peripheral_;
}
@end

@implementation peripheralsimpleobjc


-(instancetype) initWithDelegate:(id<peripheralsimpleobjc_delegate>) delegate
{
    self = [super init];
    if(self)
    {
        delegate_ = delegate;
        peripheral_ = new peripheralsimpleobjcimpl(self);
    }
    return self;
}

-(void) dealloc
{
    delete peripheral_;
}

-(void) write_file:(NSString *)centralAddr data:(NSString *)data identifier:(int)identifier
{
    try {
        //peripheral_->write_file(<#btle::device &central#>, <#std::ostream &stream#>)
        // TODO
    } catch (std::runtime_error& err) {
        _log("Failed to write file due to error: %s",err.what());
    }
}

@end
