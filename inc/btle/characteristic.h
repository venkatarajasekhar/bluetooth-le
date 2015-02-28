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
        characteristic(const std::string& data,
                       const btle::uuid& uid);
        characteristic(const btle::uuid& uid);
        characteristic(const btle::uuid& uid,
                       uint8_t properties);
        characteristic(const btle::uuid& uid,
                       uint8_t properties,
                       uint16_t attribute_handle,
                       uint16_t characteristic_properties);
        characteristic(const characteristic& other);

    public:

        uint8_t properties() const;
        const btle::uuid& uuid() const;

        // operators
        characteristic& operator << (const descriptor& desc);

        bool contains_descriptor_type(uint16_t type) const;

    private:

        btle::uuid    uuid_;
        uint16_t attribute_handle_;
        uint16_t characteristic_value_handle_;
        uint8_t characteristic_properties_;
        /**
         * @brief instance_id_, unique instance id NOTE non supported by all plugins
         */
        int instance_id_;
        std::vector<descriptor> descriptors_;

    };
}

#endif // CHARACTERISTIC_H
