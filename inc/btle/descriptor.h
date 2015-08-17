#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include <vector>
#include "btle/base.h"

namespace btle {

    #define CHARACTERISTIC_EXTENDED_PROPERTIES   0x2900
    const unsigned int CHARACTERISTIC_EXTENDED_PROPERTIES = 0x2900;
    #undef CHARACTERISTIC_EXTENDED_PROPERTIES
    #define CHARACTERISTIC_USER_DESCRIPTION      0x2901
    const unsigned int CHARACTERISTIC_USER_DESCRIPTION = 0x2901;
    #undef CHARACTERISTIC_USER_DESCRIPTION
    #define CLIENT_CHARACTERISTIC_CONFIGURATION  0x2902
    const unsigned int CLIENT_CHARACTERISTIC_CONFIGURATION = 0x2902;
    #undef CLIENT_CHARACTERISTIC_CONFIGURATION
    #define SERVER_CHARACTERISTIC_CONFIGURATION  0x2903
    const unsigned int SERVER_CHARACTERISTIC_CONFIGURATION = 0x2903;
    #undef SERVER_CHARACTERISTIC_CONFIGURATION
    #define CHARACTERISTIC_FORMAT                0x2904
    const unsigned int CHARACTERISTIC_FORMAT = 0x2904;
    #undef CHARACTERISTIC_FORMAT
    #define CHARACTERISTIC_AGGREGATE_FORMAT      0x2905
    const unsigned int CHARACTERISTIC_AGGREGATE_FORMAT = 0x2905;
    #undef CHARACTERISTIC_AGGREGATE_FORMAT

    class BTLE_API descriptor: public base
    {
    public:
        descriptor();
        descriptor(uint16_t type);
        descriptor(uint16_t type,
                   bool notifying);
        descriptor(uint16_t type,
                   uint16_t handle);
        descriptor(const descriptor& other);

        uint16_t type() const;
        uint16_t handle() const;
        bool is_notifying() const;
        void set_notifying(bool notifying);
        // operators
        bool operator == (const descriptor& other) const;
        
    private:
        uint16_t type_;
        uint16_t handle_;
        bool is_notifying_;
    };
    
    typedef std::vector<descriptor> descriptors;
}

#endif // DESCRIPTOR_H
