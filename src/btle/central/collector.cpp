
#include "btle/exceptions/attribute_not_found.h"
#include "btle/exceptions/attribute_not_readable.h"
#include "btle/exceptions/attribute_not_writable.h"
#include "btle/exceptions/device_not_connected.h"
#include "btle/exceptions/service_not_found.h"

#include "btle/central/collector.h"
#include "btle/central/centralpluginfactory.h"
#include "btle/gatt_services/gattservicefactory.h"
#include "btle/verify.h"
#include "btle/log.h"


#include "btle/bdascanfilter.h"
#include "btle/uuidscanfilter.h"

namespace {
    enum collector_flags{
        CLIENT_SCAN   = 0x01,
        INTERNAL_SCAN = 0x02
    };
}

using namespace btle::central;
using namespace btle::gatt_services;

collector::collector()
: notify_uuids_(),
  read_uuids_(),
  plugin_(NULL),
  connectionhandler_(),
  flags_(0),
  filters_(),
  state_(STATE_POWERED_UNKNOWN)
{
    centralpluginfactory::instance().populate(plugins_, *this);
    gatt_service_list services;
    gattservicefactory::instance().populate(services);
    // setup automatically all included gatt services notifications
    for( gatt_service_iterator it = services.begin(); it != services.end(); ++it )
    {
        for( uuid_iterator_const it_uuid = (*it)->mandatory_notifications().begin();
             it_uuid != (*it)->mandatory_notifications().end(); ++it_uuid )
        {
            notify_uuids_.push_back(*it_uuid);
        }
    }
    gattservicefactory::instance().deplete(services);
}

collector::~collector()
{
    for( scan_filters::iterator it = filters_.begin(); it != filters_.end(); ++it )
    {
        delete (*it);
    }
}

int collector::auto_start()
{
    plugin_ = plugins_[0];
    connectionhandler_.setup(plugin_);
    return plugin_->start();
}

/**
 * @brief collector::add_scan_filter,
 * adds abstract scan filter, library has build-in filters which can be used @see uuidscanfilter and
 * bdascanfilter,
 * @param filter, takes owner ship
 */
void collector::add_scan_filter(scanfilterbase* filter)
{
    filters_.push_back(filter);
}

/**
 * @brief collector::clear_scan_filter
 * @param filter
 */
void collector::clear_scan_filter(scanfilterbase* filter)
{
    for( scan_filters::iterator it = filters_.begin(); it != filters_.end(); ++it )
    {
        if( (*it) == filter )
        {
            delete (*it);
            filters_.erase(it);
            return;
        }
    }
}

/**
 * @brief collector::clear_scan_filters
 */
void collector::clear_scan_filters()
{
    filters_.clear();
}

/**
 * @brief collector::start_scan
 */
void collector::start_scan()
{
    verify(plugin_)
    flags_ |= CLIENT_SCAN;
    if( state_ == STATE_POWERED_ON ) plugin_->start_scan();
    else _log_warning("BT STATE NOT POWERED!");
}

/**
 * @brief collector::stop_scan
 */
void collector::stop_scan()
{
    verify(plugin_)
    flags_ &= ~CLIENT_SCAN;
    plugin_->stop_scan();
}

/**
 * @brief collector::connection_handler
 * @return
 */
connectionhandler& collector::connection_handler()
{
    return connectionhandler_;
}

/**
 * @brief collector::set_auto_read_values, setup characteristic uuids to be read if found
 * @param list
 */
void collector::set_auto_read_values(const uuid_list& list)
{
    read_uuids_ = list;
}

/**
 * @brief collector::set_auto_notify_values, setup notification/indications to be enabled automatically
 *                                           note this overrides default set , which has been loaded from gatt service factory, use this functionality with
 *                                           extra care
 * @param list
 */
void collector::set_auto_notify_values(const uuid_list& list)
{
    notify_uuids_ = list;
}

/**
 * @brief collector::connect_device, for most basic use of the lib you only need
 *                                   to call this function after start, and wait the device is connected
 *                                   and start receiving heart rate etc...
 * @param addr
 */
void collector::connect_device(const bda& addr)
{
    verify(plugin_)
    if( device* dev = fetch_device(addr) )
    {
        connectionhandler_.connect_device(*dev);
    }
    else
    {
        dev = plugin_->allocate_new_device(addr);
        plugin_->devices().push_back(dev);
        connectionhandler_.connect_device(*dev);
    }
}

/**
 * @brief collector::connect_device
 * @param dev
 */
void collector::connect_device(device& dev)
{
    verify(plugin_)
    connectionhandler_.connect_device(dev);
}

/**
 * @brief collector::disconnect_device
 * @param dev
 */
void collector::disconnect_device(device& dev)
{
    verify(plugin_)
    connectionhandler_.disconnect_device(dev);
}

/**
 * @brief collector::disconnect_device
 * @param addr
 */
void collector::disconnect_device(const bda& addr)
{
    verify(plugin_)
    if( device* dev = fetch_device(addr) )
    {
        // fail safe check that device exists
        connectionhandler_.disconnect_device(*dev);
    }
}

/**
 * @brief collector::read_characteristic_value
 * @param dev
 * @param uid
 * @throws device_not_connected, device state is something else than CONNECTED
 */
void collector::read_characteristic_value(device& dev, const uuid& uid)
{
    verify(plugin_)
    if( dev.state() == btle::DEVICE_CONNECTED )
    {
        if( const characteristic* chr = dev.db().fetch_characteristic(uid) )
        {
            if( chr->properties() & btle::GATT_READ )
            {
                const service* srv = dev.db().fetch_service_by_chr_uuid(uid);
                verify(srv);
                plugin_->read_characteristic_value(dev,*srv,*chr);
                return;
            }
            throw btle::exceptions::attribute_not_readable("attribute cannot be read");
        }
        throw btle::exceptions::attribute_not_found("device does not contain this uuid");
    }
    throw btle::exceptions::device_not_connected("device not connected");
}

/**
 * @brief collector::read_characteristic_value
 * @param dev
 * @param pair
 */
void collector::read_characteristic_value(device& dev, const uuid_pair& pair)
{
    verify(plugin_)
    if( dev.state() == btle::DEVICE_CONNECTED )
    {
        if( const characteristic* chr = dev.db().fetch_characteristic(pair) )
        {
            if( chr->properties() & btle::GATT_READ )
            {
                const service* srv = dev.db().fetch_service(pair.first);
                verify( srv );
                plugin_->read_characteristic_value(dev,*srv,*chr);
                return;
            }
            throw btle::exceptions::attribute_not_readable("attribute cannot be read");
        }
        throw btle::exceptions::attribute_not_found("device does not contain this uuid");
    }
    throw btle::exceptions::device_not_connected("device not connected");
}

/**
 * @brief collector::write_characteristic_value
 * @param dev
 * @param uid
 */
void collector::write_characteristic_value(device& dev, const uuid& uid, const std::string& data, bool write_with_out_resp)
{
    verify(plugin_)
    if( dev.state() == btle::DEVICE_CONNECTED )
    {
        if( const characteristic* chr = dev.db().fetch_characteristic(uid) )
        {
            if( !write_with_out_resp )
            {
                if( chr->properties() & btle::GATT_WRITE )
                {
                    const service* srv = dev.db().fetch_service_by_chr_uuid(uid);
                    verify( srv != NULL );
                    plugin_->write_characteristic_value(dev,*srv,*chr,data,btle::GATT_WRITE);
                    return;
                }
            }
            if( chr->properties() & btle::GATT_WRITE_WITHOUT_RESPONSE )
            {
                const service* srv = dev.db().fetch_service_by_chr_uuid(uid);
                verify( srv );
                plugin_->write_characteristic_value(dev,*srv,*chr,data,btle::GATT_WRITE_WITHOUT_RESPONSE);
                return;
            }
            throw btle::exceptions::attribute_not_writable("attribute cannot be written");
        }
        throw btle::exceptions::attribute_not_found("device does not contain this uuid");
    }
    throw btle::exceptions::device_not_connected("device not connected");
}

/**
 * @brief collector::write_characteristic_value
 * @param dev
 * @param pair
 */
void collector::write_characteristic_value(device& dev, const uuid_pair& pair, const std::string& data, bool write_with_out_resp)
{
    verify(plugin_)
    if( dev.state() == btle::DEVICE_CONNECTED )
    {
        if( const characteristic* chr = dev.db().fetch_characteristic(pair.second) )
        {
            if( !write_with_out_resp )
            {
                if( chr->properties() & btle::GATT_WRITE )
                {
                    const service* srv = dev.db().fetch_service(pair.first);
                    verify( srv );
                    plugin_->write_characteristic_value(dev,*srv,*chr,data,btle::GATT_WRITE);
                    return;
                }
            }
            if( chr->properties() & btle::GATT_WRITE_WITHOUT_RESPONSE )
            {
                const service* srv = dev.db().fetch_service(pair.first);
                verify( srv );
                plugin_->write_characteristic_value(dev,*srv,*chr,data,btle::GATT_WRITE_WITHOUT_RESPONSE);
                return;
            }
            throw btle::exceptions::attribute_not_writable("attribute cannot be written");
        }
        throw btle::exceptions::attribute_not_found("device does not contain this uuid");
    }
    throw btle::exceptions::device_not_connected("device not connected");
}

/**
 * @brief collector::set_characteristic_notify
 * @param dev
 * @param uid
 * @param notify
 */
void collector::set_characteristic_notify(device& dev, const uuid& uid, bool notify)
{
    verify(plugin_)
    verify(plugin_)
    if( dev.state() == btle::DEVICE_CONNECTED )
    {
        if( const characteristic* chr = dev.db().fetch_characteristic(uid) )
        {
            if( chr->properties() & btle::GATT_READ )
            {
                const service* srv = dev.db().fetch_service_by_chr_uuid(uid);
                verify( srv );
                // TODO fix descriptor
                descriptor desc(CLIENT_CHARACTERISTIC_CONFIGURATION);
                plugin_->write_descriptor(dev,*srv,*chr,desc,notify);
                return;
            }
            throw btle::exceptions::attribute_not_readable("attribute cannot be read");
        }
        throw btle::exceptions::attribute_not_found("device does not contain this uuid");
    }
    throw btle::exceptions::device_not_connected("device not connected");
}

/**
 * @brief collector::set_characteristic_notify
 * @param dev
 * @param pair
 * @param notify
 */
void collector::set_characteristic_notify(device& dev, const uuid_pair& pair, bool notify)
{
    verify(plugin_)
    if( dev.state() == btle::DEVICE_CONNECTED )
    {
        if( const characteristic* chr = dev.db().fetch_characteristic(pair) )
        {
            if( chr->properties() & btle::GATT_READ )
            {
                const service* srv = dev.db().fetch_service(pair.first);
                verify( srv );
                plugin_->read_characteristic_value(dev,*srv,*chr);
                return;
            }
            throw btle::exceptions::attribute_not_readable("attribute cannot be read");
        }
        throw btle::exceptions::attribute_not_found("device does not contain this uuid");
    }
    throw btle::exceptions::device_not_connected("device not connected");
}

void collector::plugin_state_changed(central_plugin_state state)
{
    switch (state) {
        case STATE_POWERED_ON:
        {
            if( flags_ & CLIENT_SCAN )
            {
                plugin_->start_scan();
            }
            break;
        }
        default:
            break;
    }
}

void collector::device_discovered(device& dev)
{
    connectionhandler_.advertisement_head_received(dev);
    if( flags_ & CLIENT_SCAN )
    {
        for( std::vector<scanfilterbase*>::iterator it = filters_.begin(); it != filters_.end(); ++it )
        {
            if( (*it)->process(dev) )
            {
                // propagate callback
                device_discovered_cb(dev);
                return;
            }
        }
        // TODO add still optional manaufacturer data filter
        device_discovered_cb(dev);
    }
}

void collector::device_connected(device& dev)
{
    connectionhandler_.device_connected(dev);
    plugin_->discover_services(dev);
}

void collector::device_disconnected(device& dev)
{
    connectionhandler_.device_disconnected(dev);
}

void collector::device_services_discovered(device& dev, const service_list& services, const error& err)
{
    if( err.code() == 0 )
    {
        dev.db() << services;
        for( service_iterator_const it = services.begin(); it != services.end(); ++it )
        {
            if( gattservicebase* gatt_srv = dev.gatt_service(it->uuid()) )
            {
                // TODO give heads up to client, the device has e.g. Heart Rate Service etc...
                // something like device_features_updated
                device_gatt_service_discovered_cb(dev,gatt_srv);
            }
            plugin_->discover_characteristics(dev,(*it));
        }
    }
    else device_service_discovery_failed_cb(dev,services,err);
}

void collector::device_characteristics_discovered(device& dev, const service& srv, const chr_list& chrs, const error& err)
{
    if( err.code() == 0 )
    {
        // first check auto read
        for( chr_iterator_const it = chrs.begin(); it != chrs.end(); ++it )
        {
            for( uuid_iterator_const it_uuid = read_uuids_.begin(); it_uuid != read_uuids_.end(); ++it_uuid )
            {
                if( (*it) == (*it_uuid) &&
                    it->properties() & GATT_READ )
                {
                    plugin_->read_characteristic_value(dev,srv,(*it));
                }
            }
        }
        // second check notify list
        for( chr_iterator_const it = chrs.begin(); it != chrs.end(); ++it )
        {
            for( uuid_iterator_const it_uuid = notify_uuids_.begin(); it_uuid != notify_uuids_.end(); ++it_uuid )
            {
                if( it->uuid() == (*it_uuid) &&
                    ( it->properties() & GATT_INDICATE ||
                      it->properties() & GATT_NOTIFY ))
                {
                    plugin_->set_characteristic_notify(dev,srv,(*it),true);
                }
            }
        }
    }
    else device_characteristic_discovery_failed_cb(dev,srv,chrs,err);
}

void collector::device_characteristic_read(
    device& dev,
    const service& srv,
    const characteristic& chr,
    const std::string& data,
    const error& err)
{
    if( gattservicebase* gatt_service = dev.gatt_service(srv.uuid()) )
    {
        if( gatt_service->contains_characteristic_uuid(chr.uuid()) )
        {
            gatt_service->process_service_value_read(chr.uuid(),(const uint8_t*)data.c_str(),data.size(), err);
            device_service_value_updated_cb(dev,gatt_service);
        }
    }
    //
}

void collector::device_characteristic_written(device& dev, const service& srv, const characteristic& chr, const error& err)
{
    // TODO
}

void collector::device_characteristic_nofication_state_changed(device& dev, const service& srv, const characteristic& chr, bool notify, const error& err)
{
    if( gattservicebase* gatt_service = dev.gatt_service(srv.uuid()) )
    {
        gatt_service->set_active(chr.uuid(),err.code() == 0 ? notify : false);
    }
}

void collector::device_characteristic_notify_data_updated(device& dev, const service& srv, const characteristic& chr, const std::string& data)
{
    // notification or indication has been received
    if( gattservicebase* gatt_service = dev.gatt_service(srv.uuid()) )
    {
        if( gatt_service->contains_characteristic_uuid(chr.uuid()) )
        {
            gatt_service->process_service_notify_data(chr.uuid(),(const uint8_t*)data.c_str(),data.size());
            device_service_value_updated_cb(dev,gatt_service);
        }
    }
}

/**
 * @brief collector::device_gatt_service_discovered_cb, this callbacks idea is
 * to be used in the next way:
 * if( srv )
 * {
 *      switch( srv->service_uuid().uuid16bit() )
 *      {
 *          case HEART_RATE_SERVICE:
 *          {
 *              // enable Heart rate specific ui etc...
 *              break;
 *          }
 *          etc...
 *      }
 * }
 * @param dev
 * @param srv
 */
void collector::device_gatt_service_discovered_cb(device& dev, const gattservicebase* srv)
{
    _log_warning("Device contains some included service or 3rd added service device: %s gatt uuid: %s",
                 dev.description().c_str(),
                 srv->service_uuid().description().c_str());
}

void collector::device_service_discovery_failed_cb(device& dev, const service_list& services, const error& err)
{
    _log_warning("device service discovery failed, override this callback for further logic device desc: %s error: %s",
                 dev.description().c_str(),
                 err.description().c_str());
}

void collector::device_characteristic_discovery_failed_cb(device& dev, const service& srv, const chr_list& chrs, const error& err)
{
    _log_warning("device service discovery failed, override this callback for further logic");
}

btle::device* collector::fetch_device(const bda& addr)
{
    verify(plugin_)
    for( device_iterator it = plugin_->devices().begin(); it != plugin_->devices().end(); ++it )
    {
        if( (*it)->addr() == addr )
        {
            return (*it);
        }
    }
    return NULL;
}

