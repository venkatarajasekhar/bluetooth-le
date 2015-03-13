#ifndef DEVICE_H
#define DEVICE_H

#include "btle/base.h"
#include "btle/advertisementdata.h"
#include "btle/gattdatabase.h"
#include "btle/bda.h"
#include "btle/rssifilter.h"

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

    class device: public base
    {
    public:
        device();
        ~device();

    public: //

        const std::string& name();
        const advertisementdata* advertisement_data_for_key(btle::advertisement_type key) const;
        gattdatabase& db();
        const gattdatabase& db() const;
        rssifilter& rssi_filter();
        const rssifilter& rssi_filter() const;
        connection_state state() const;
        std::string state_string() const;
        const bda& addr() const;
        bool operator == (const device& other) const;

    public:

        void set_state(connection_state state);
        friend class connectionhandler;
        int reconnections_;

    protected:

        /**
         * @brief advertisement_data_, only peripheral device has advertisement fields
         * this does not store history, only current adv data, or updates an field
         */
        std::map<btle::advertisement_type,btle::advertisementdata> advertisement_data_;
        std::string name_;
        gattdatabase db_;
        connection_state state_;
        bda bda_;
        rssifilter rssifilter_;
    };

    typedef std::vector<device*> device_list;
    typedef std::vector<device*>::iterator device_iterator;
    typedef std::vector<device*>::const_iterator device_iterator_const;
}

#endif // DEVICE_H

