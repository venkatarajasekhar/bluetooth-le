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
         GATT_BROADCAST                        = 0x01,
         GATT_READ                             = 0x02,
         GATT_WRITE_WITHOUT_RESP               = 0x04,
         GATT_WRITE                            = 0x08,
         GATT_NOTIFY                           = 0x10,
         GATT_INDICATE                         = 0x20,
         GATT_AUTHENTICATED_SIGNED_WRITE       = 0x40,
         GATT_EXTENDED_PROPERTIES              = 0x80
    };

    class BTLE_API characteristic: public base
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
        uint8_t attribute_handle() const;

        // operators
        characteristic& operator << (const descriptor& desc);
        bool operator == (const characteristic& other) const;

        bool contains_descriptor_type(uint16_t type) const;

    private:

        btle::uuid    uuid_;
        uint16_t attribute_handle_;
        uint16_t characteristic_value_handle_;
        uint8_t  characteristic_properties_;
        /**
         * @brief instance_id_, unique instance id NOTE non supported by all plugins
         */
        int instance_id_;
        std::vector<descriptor> descriptors_;
    };

    typedef std::vector<characteristic>::iterator chr_iterator;
    typedef std::vector<characteristic>::const_iterator chr_iterator_const;
    typedef std::vector<characteristic> chr_list;
}

#endif // CHARACTERISTIC_H
