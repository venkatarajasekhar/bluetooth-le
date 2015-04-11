#ifndef DEVICE_H
#define DEVICE_H

#include "btle/base.h"
#include "btle/advertisementdata.h"
#include "btle/gattdatabase.h"
#include "btle/bda.h"
#include "btle/rssifilter.h"
#include "btle/gatt_services/gattservicebase.h"
#include "btle/connectionparameters.h"
#include "btle/advertisementfields.h"

#include <map>

namespace btle {
    // bluetooth le device presentation class, can be a peripheral or central device,
    // depending on api used
    enum connection_state{
        DEVICE_DISCONNECTED,
        DEVICE_DISCONNECTING,
        DEVICE_DISCONNECTION_PARK,
        DEVICE_CONNECTING,
        DEVICE_CONNECTED,
        DEVICE_CONNECTION_PARK
    };
    
    enum advertisement_type
    {
        DEVICE_ADVERTISEMENT_CONNECTABLE_UNDIRECTED,
        DEVICE_ADVERTISEMENT_NON_CONNECTABLE,
        DEVICE_ADVERTISEMENT_DIRECTED
    };

    class BTLE_API device: public base
    {
    public:
        device(const bda& addr);
        ~device();

    public: //
        // advertisement data related
        const std::string& name();
        const advertisementdata* advertisement_data_for_key(btle::advertisement_type key) const;
        // gattdata base ralated
        gattdatabase& db();
        const gattdatabase& db() const;
        // rssi related
        rssifilter& rssi_filter();
        // connection state related
        connection_state state() const;
        std::string state_string() const;

        const bda& addr() const;
        // build-in gatt service related
        const gatt_services::gattservicebase* gatt_service(const uuid& uid) const;
        gatt_services::gattservicebase* gatt_service(const uuid& uid);

        advertisementfields& advertisement_fields();
        
        connectionparameters& parameters();
        // operators
        bool operator == (const device& other) const;
        btle::advertisement_type advertisement_type() const;

    public: // from base

        std::string description() const;

    public:

        void set_state(connection_state state);
        friend class connectionhandler;
        int reconnections_;

    protected:

        advertisementfields advertisement_fields_;
        std::string name_;
        gattdatabase db_;
        connection_state state_;
        bda bda_;
        rssifilter rssifilter_;
        gatt_services::gatt_service_list gatt_services_;
        connectionparameters parameters_;
        btle::advertisement_type advertisement_type_;
    };

    typedef std::vector<device*> device_list;
    typedef std::vector<device*>::iterator device_iterator;
    typedef std::vector<device*>::const_iterator device_iterator_const;
}

#endif // DEVICE_H

