
#include "btle/peripheral/peripheralobjc.h"

class peripheralobjcimpl: public btle::peripheral::peripheral
{
private:
    peripheralobjc* peripheral_;
public:
    
    peripheralobjcimpl(peripheralobjc* peripheral)
    : peripheral_(peripheral)
    {
    }
    
    void btle_ftp_in_progress_cb(device& dev, double progress, const std::string& data, int identifier)
    {
        [peripheral_->delegate_ btle_ftp_in_progress:dev progress:progress data:data identifier:identifier];
    }
    
    void btle_ftp_out_progress_cb(device& dev, double progress, int identifier)
    {
        [peripheral_->delegate_ btle_ftp_out_progress:dev progress:progress identifier:identifier];
    }
    
    void plugin_state_changed_cb(plugin_state state)
    {
        [peripheral_->delegate_ plugin_state_changed:state];
    }
    
    void advertising_started_cb(error& err)
    {
        [peripheral_->delegate_ advertising_started:err];
    }
    
    void advertising_stopped_cb()
    {
        [peripheral_->delegate_ advertising_stopped];
    }
    
    void service_added_cb(service& srv, const error& err)
    {
        [peripheral_->delegate_ service_added:srv err:err];
    }
    
    void central_connected_cb(device& dev)
    {
        [peripheral_->delegate_ central_connected:dev];
    }
    
    void central_disconnected_cb(device& dev)
    {
        [peripheral_->delegate_ central_disconnected:dev];
    }
    
    void descriptor_written_cb(device& central, const service& srv, const characteristic& chr, const descriptor& desc)
    {
        [peripheral_->delegate_ descriptor_written:central srv:srv chr:chr desc:desc];
    }
    
    btle::attributerequest characteristic_read_cb(device& central, const service& srv, const characteristic& chr)
    {
        return [peripheral_->delegate_ characteristic_read:central srv:srv chr:chr];
    }
    
    void characteristic_write_cb(device& central,const service& srv,const characteristic& chr,const std::string& data)
    {
        [peripheral_->delegate_ characteristic_write:central srv:srv chr:chr data:data];
    }
};

@implementation peripheralobjc


-(instancetype) initWithDelegate:(id<peripheralobjc_delegate>) delegate
{
    self = [super init];
    if(self)
    {
        delegate_ = delegate;
        peripheral_ = new peripheralobjcimpl(self);
    }
    return self;
}

-(void) dealloc
{
    delete peripheral_;
}

@end
