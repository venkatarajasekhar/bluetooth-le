
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

int peripheral::start(const std::string& plugin_name)
{
    stop();
    for( std::vector<peripheralplugininterface*>::iterator it = plugins_.begin(); it != plugins_.end(); ++it )
    {
        if( (*it)->name().compare(plugin_name) != std::string::npos )
        {
            plugin_ = (*it);
            if( int err = plugin_->start() )
            {
                plugin_ = NULL;
                return err;
            }
            db_.invalidate();
            // by default add library service
            db_ << (service(uuid(BTLE_SERVICE))
                    << characteristic(uuid(BTLE_MTU),GATT_WRITE_WITHOUT_RESPONSE|GATT_NOTIFY)
                    << characteristic(uuid(BTLE_VERSION),GATT_READ));
            return 0;
        }
    }
    return -1;
}

int peripheral::auto_start()
{
    assert(plugins_.size());
    stop();
    plugin_ = plugins_[0];
    if( int err = plugin_->start() )
    {
        plugin_ = NULL;
        return err;
    }
    return 0;
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

