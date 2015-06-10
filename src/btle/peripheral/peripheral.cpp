
#include "btle/peripheral/peripheral.h"
#include "btle/peripheral/peripheralpluginfactory.h"
#include "btle/gatt_services/btlelibservice.h"

#include <assert.h>

using namespace btle::peripheral;

namespace {
}

peripheral::peripheral()
: plugin_(NULL),
  plugins_(),
  flags_(0),
  plugins_available_(),
  db_()
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
                        << characteristic(uuid(BTLE_MTU),GATT_WRITE_WITHOUT_RESPONSE|GATT_NOTIFY)
                        << characteristic(uuid(BTLE_VERSION),GATT_READ));
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
                << characteristic(uuid(BTLE_MTU),GATT_WRITE_WITHOUT_RESPONSE|GATT_NOTIFY)
                << characteristic(uuid(BTLE_VERSION),GATT_READ));
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

