#ifndef CHARACTERISTIC_H
#define CHARACTERISTIC_H

#include "btle/base.h"
#include "btle/uuid.h"
#include "btle/descriptor.h"

#include <vector>

namespace btle {

    /**
     * @brief The characteristic_properties enum, characteristic properties check
     * bluetooth spec for more details
     */
    enum characteristic_properties{
         GATT_Broadcast                        = 0x01,
         GATT_Read                             = 0x02,
         GATT_Write_Without_Resp               = 0x04,
         GATT_Write                            = 0x08,
         GATT_Notify                           = 0x10,
         GATT_Indicate                         = 0x20,
         GATT_Authenticated_Signed_Writes      = 0x40,
         GATT_Extented_Properties              = 0x80
    };

    class characteristic: public base
    {
    public:
        characteristic();
        characteristic(const std::string& data);
        characteristic(const characteristic& other);
        ~characteristic();

    public:

        unsigned char properties() const;

    private:

        uuid _uuid;
        int _attribute_handle;
        int _characteristic_value_handle;
        unsigned char _characteristic_properties_;
        /**
         * @brief instance_id_, unique instance id NOTE non supported by all plugins
         */
        int instance_id_;
        std::vector<descriptor> _descriptors;

    };
}

#endif // CHARACTERISTIC_H
