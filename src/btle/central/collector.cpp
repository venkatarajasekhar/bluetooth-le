

#include "btle/exceptions/attribute_not_found.h"
#include "btle/exceptions/attribute_not_readable.h"
#include "btle/exceptions/attribute_not_writable.h"
#include "btle/exceptions/device_not_connected.h"
#include "btle/exceptions/service_not_found.h"

#include "btle/central/collector.h"
#include "btle/gatt_services/gattservicefactory.h"
#include "btle/verify.h"

using namespace btle::central;
using namespace btle::gatt_services;

collector::collector()
{
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

/**
 * @brief collector::set_scan_filter, setup scan filter for certain type of devices e.g.
 *        Heart Rate Service etc..
 * @param filter
 */
void collector::set_scan_filter(const uuid_list& filter)
{
    filter_ = filter;
}

/**
 * @brief collector::set_scan_filter, setup bda filter if the device does not advertise a certain type of service,
 *        you may want to still "monitor" a device or devices
 * @param bdas
 */
void collector::set_scan_filter(const bda_list &bdas)
{
    bda_filter_ = bdas;
}

/**
 * @brief collector::start_scan
 */
void collector::start_scan()
{
    verify(plugin_)
    plugin_->start_scan();
}

/**
 * @brief collector::stop_scan
 */
void collector::stop_scan()
{
    verify(plugin_)
    plugin_->stop_scan();
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
            if( chr->properties() & btle::GATT_WRITE_WITHOUT_RESP )
            {
                const service* srv = dev.db().fetch_service_by_chr_uuid(uid);
                verify( srv );
                plugin_->write_characteristic_value(dev,*srv,*chr,data,btle::GATT_WRITE_WITHOUT_RESP);
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
            if( chr->properties() & btle::GATT_WRITE_WITHOUT_RESP )
            {
                const service* srv = dev.db().fetch_service(pair.first);
                verify( srv );
                plugin_->write_characteristic_value(dev,*srv,*chr,data,btle::GATT_WRITE_WITHOUT_RESP);
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
                plugin_->set_characteristic_notify(dev,*srv,*chr,notify);
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

void collector::device_discovered(device& dev)
{
    // check first bda list
    if( bda_filter_.size() )
    {
        for( bda_iterator_const it = bda_filter_.begin(); it != bda_filter_.end(); ++it )
        {
            if( (*it) == dev.addr() )
            {
                // propagate callback
                return;
            }
        }
    }
    // secondary check uuid filter list
    if( filter_.size() )
    {
        for( uuid_iterator_const it = filter_.begin(); it != filter_.end(); ++it )
        {
            if( dev.is_service_advertiset((*it)) )
            {
                // propagate callback
                return;
            }
        }
    }
}

void collector::device_services_discovered(device& dev, const service_list& services, const error& err)
{
    if( err.code() == 0 )
    {
        for( service_iterator_const it = services.begin(); it != services.end(); ++it )
        {
            if( gattservicebase* gatt_srv = dev.gatt_service(it->uuid()) )
            {
                // TODO give heads up to client, the device has e.g. Heart Rate Service etc...
                // something like device_features_updated
            }
            plugin_->discover_characteristics(dev,(*it));
        }
    }
    // else inform optional callback to client
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
                if( (*it) == (*it_uuid) &&
                    ( it->properties() & GATT_INDICATE ||
                      it->properties() & GATT_NOTIFY ))
                {
                    plugin_->set_characteristic_notify(dev,srv,(*it),true);
                }
            }
        }
    }
    // else inform optional callback to client about error
}

void collector::device_characteristic_read(device& dev, const service& srv, const characteristic& chr, const std::string& data, const error& err)
{
    if( err.code() == 0 )
    {
        if( gattservicebase* gatt_service = dev.gatt_service(srv.uuid()) )
        {
            if( gatt_service->contains_characteristic_uuid(chr.uuid()) )
            {
                gatt_service->process_service_data(chr.uuid(),(const uint8_t*)data.c_str(),data.size());
            }
        }
    }
    //
}

void collector::device_characteristic_written(device& dev, const service& srv, const characteristic& chr, const error& err)
{

}

void collector::device_characteristic_nofication_state_changed(device& dev, const service& srv, const characteristic& chr, bool notify, const error& err)
{

}

void collector::device_characteristic_notify_data_updated(device& dev, const service& srv, const characteristic& chr, const std::string& data)
{
    // notification or indication has been received
    if( gattservicebase* gatt_service = dev.gatt_service(srv.uuid()) )
    {
        if( gatt_service->contains_characteristic_uuid(chr.uuid()) )
        {
            gatt_service->process_service_data(chr.uuid(),(const uint8_t*)data.c_str(),data.size());
        }
    }
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

