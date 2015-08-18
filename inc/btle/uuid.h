#ifndef UUID_H
#define UUID_H

#include "btle/base.h"

#include <vector>

namespace btle {

    #define UUID_128_BIN_LENGTH 16
    const unsigned int UUID_128_BIN_LENGTH = 16;
    #undef  UUID_128_BIN_LENGTH
    #define UUID_16_BIN_LENGTH  2
    const unsigned int UUID_16_BIN_LENGTH = 2;
    #undef UUID_16_BIN_LENGTH
    
    class BTLE_API uuid: public base
    {
    public:
        uuid();
        uuid(const uuid& other);
        explicit uuid(uint16_t uuid16);
        explicit uuid(const std::string& uuid_str);
        explicit uuid(const uint8_t uuid128[UUID_128_BIN_LENGTH]);

        // getters
        uint16_t uuid16bit() const;
        const std::string& uuid128bit() const;

        // evaluators
        bool is16bit() const;
        bool is128bit() const;

        // operators
        bool operator == (const uuid& other) const;
        bool operator == (uint16_t uuid16) const;
        bool operator == (const uint8_t uuid128[UUID_128_BIN_LENGTH]) const;
        bool operator == (const std::string& uuid_str) const;
        bool operator != (const uuid& other) const;
        bool operator != (uint16_t uuid16) const;
        bool operator != (const uint8_t uuid128[UUID_128_BIN_LENGTH]) const;
        bool operator != (const std::string& uuid_str) const;

    // from base

        std::string to_string() const;

    private:
        uint16_t uuid16_;
    };

    typedef std::pair<uuid,uuid> uuid_pair;
    typedef std::vector<uuid> uuid_list;
    typedef std::vector<uuid>::iterator uuid_iterator;
    typedef std::vector<uuid>::const_iterator uuid_iterator_const;
}

#endif // UUID_H
