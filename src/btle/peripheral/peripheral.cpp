
#include "btle/peripheral/peripheral.h"
#include "btle/peripheral/peripheralpluginfactory.h"
#include "btle/gatt_services/btlelibservice.h"
#include "btle/log.h"

#include <assert.h>

using namespace btle::peripheral;

namespace {
}

peripheral::peripheral()
: plugin_(NULL),
  plugins_(),
  flags_(0),
  plugins_available_(),
  db_(),
  btlelib_service_()
{
    peripheralpluginfactory::instance().populate(plugins_,*this);
    for( std::vector<peripheralplugininterface*>::const_iterator it = plugins_.begin(); it != plugins_.end(); ++it )
    {
        plugins_available_.push_back((*it)->name());
    }
}

const std::vector<std::string>& peripheral::plugins_available() const
{
    return plugins_available_;
}

void peripheral::start(const std::string& plugin_name)
{
    stop();
    for( std::vector<peripheralplugininterface*>::iterator it = plugins_.begin(); it != plugins_.end(); ++it )
    {
        if( (*it)->name().compare(plugin_name) != std::string::npos )
        {
            try
            {
                plugin_ = (*it);
                plugin_->start() ;
                db_.invalidate();
                // by default add library service
                db_ << (service(uuid(BTLE_SERVICE))
                        << characteristic(uuid(BTLE_MTU),GATT_WRITE_WITHOUT_RESPONSE|GATT_NOTIFY,NULL)
                        << characteristic(uuid(BTLE_VERSION),GATT_READ,NULL));
            }
            catch(std::runtime_error& ex)
            {
                plugin_ = NULL;
                throw ex;
            }
            return;
        }
    }
}

void peripheral::auto_start()
{
    assert(plugins_.size());
    stop();
    try
    {
        plugin_ = plugins_[0];
        plugin_->start() ;
        db_.invalidate();
        // by default add library service
        db_ << (service(uuid(BTLE_SERVICE))
                << characteristic(uuid(BTLE_MTU),GATT_WRITE_WITHOUT_RESPONSE|GATT_NOTIFY,NULL)
                << characteristic(uuid(BTLE_VERSION),GATT_READ,NULL));
    }
    catch(std::runtime_error& ex)
    {
        plugin_ = NULL;
        throw ex;
    }
}

void peripheral::stop()
{
    if( plugin_ )
    {
        plugin_->stop();
        plugin_ = NULL;
    }
}

peripheral& peripheral::operator << (const service& srv)
{
    db_ << srv;
    return *this;
}

void peripheral::advertise_btle_lib_service()
{
    adv_fields fields;
    fields[GAP_ADTYPE_128BIT_COMPLETE] = advertisementdata(std::string(BTLE_SERVICE,16));
    plugin_->start_advertising(100, fields);
}

void peripheral::write_file(btle::device& central, std::ostream& stream, int identifier)
{
    btlelib_service_.write_service_value(uuid(BTLE_MTU), identifier, "TODO", &central, NULL);
}

void peripheral::plugin_state_changed(plugin_state state)
{
    
}

void peripheral::advertising_started(error& err)
{

}

void peripheral::advertising_stopped()
{

}

void peripheral::service_added(service& srv, error& err)
{

}

void peripheral::central_connected(device& dev)
{

}

void peripheral::central_disconnected(device& dev)
{

}

void peripheral::descriptor_written(device& central, service& srv, characteristic& chr, descriptor& desc)
{
    
}

btle::attributerequest peripheral::characteristic_read(device& central, service& srv, characteristic& chr)
{
    return attributerequest();
}

void peripheral::characteristic_write(device& central,service& srv,characteristic& chr,std::string& data)
{
    
}

void peripheral::notify_channel_free(device& central)
{
    
}

void peripheral::plugin_state_changed_cb(plugin_state state)
{
    
}

void peripheral::advertising_started_cb(error& err)
{
    
}

void peripheral::advertising_stopped_cb()
{
    
}

void peripheral::service_added_cb(service& srv, error& err)
{
    _log("service uuid: %s err: %s", srv.to_string().c_str(), err.to_string().c_str());
}

void peripheral::central_connected_cb(device& dev)
{
    _log("central bda: %s",dev.addr().to_string().c_str());
}

void peripheral::central_disconnected_cb(device& dev)
{
    _log("central bda: %s",dev.addr().to_string().c_str());
}

void peripheral::descriptor_written_cb(device& central, service& srv, characteristic& chr, descriptor& desc)
{
    
}

btle::attributerequest peripheral::characteristic_read_cb(device& central, service& srv, characteristic& chr)
{
    return btle::attributerequest();
}

void peripheral::characteristic_write_cb(device& central,service& srv,characteristic& chr,std::string& data)
{
    if(srv == uuid(BTLE_SERVICE))
    {
        btle::error err(0);
        btlelib_service_.process_service_value_read(chr.uuid(), (const uint8_t*)data.c_str(), data.size(),
                                                    err);
    }
}

void peripheral::btle_ftp_in_progress_cb(device& dev, double progress, const std::string& data, int identifier)
{
    _log("file transfer progress procentage: %d id: %i", progress, identifier);
}

void peripheral::btle_ftp_out_progress_cb(device& dev, double progress, int identifier)
{
    _log("file transfer progress procentage: %d id: %i", progress, identifier);
}

