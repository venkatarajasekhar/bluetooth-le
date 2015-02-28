#ifndef DEVICE_H
#define DEVICE_H

#include "btle/base.h"
#include "btle/advertisementdata.h"
#include "btle/gattdatabase.h"

#include <map>

namespace btle {
    // bluetooth le device presentation class, can be a peripheral or central device, depending on api used
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

        const std::string& name();
        const advertisementdata* advertisement_data_for_key(btle::advertisement_type key) const;
        gattdatabase& db();
        connection_state state() const;

    private:

        /**
         * @brief advertisement_data_, only peripheral device has advertisement fields
         * this does not store history, only current adv data, or updates an field
         */
        std::map<btle::advertisement_type,btle::advertisementdata> advertisement_data_;
        std::string name_;
        gattdatabase db_;
        connection_state state_;
    };
}

#endif // DEVICE_H

