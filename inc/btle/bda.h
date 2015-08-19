#ifndef BDA_H
#define BDA_H

#include <vector>
#include <stdint.h>
#include "btle/base.h"

namespace btle {

    /**
     * @brief The addr_type enum bluetooth address type, check from bluetooth spec for deeper understanding
     * NOTE not all platforms support this!
     */
    enum address_type
    {
        ADDR_PUBLIC                         = 0x00,  // Public Address
        ADDR_STATIC                         = 0x01,  // Static address
        ADDR_PRIVATE_NONRESOLVE             = 0x02,  // Non-Resolvable Private Address
        ADDR_PRIVATE_RESOLVE                = 0x03   // Resolvable Private Address
    };

    /**
     * addr len in native format
     */
    #define BDA_BIN_LENGTH 6

    /**
     * @brief The bda class, bda is the "unique" identifier of the device,
     * this is in untouched format e.g in iOS/MAC where you do not get the real
     * bda, but you get the generated uuid( this is considered bda ). in Android you get
     * bda in string format e.g 00:11:22:33:44:55 etc...
     */
    class BTLE_API bda: public base
    {
    public:
        bda();
        bda(const std::string& bda_str);
        bda(const std::string& bda_str, address_type type);
        bda(const char bda_strc[BDA_BIN_LENGTH] , address_type type);
        bda(const bda& other);
        ~bda();

    

        address_type type() const;

  // override from base

        std::string to_string() const;

        // operators
        bool operator == (const bda& other) const;

    private:
        address_type type_;
    };

    typedef std::vector<bda> bda_list;
    typedef std::vector<bda>::iterator bda_iterator;
    typedef std::vector<bda>::const_iterator bda_iterator_const;
}
#endif // BDA_H
