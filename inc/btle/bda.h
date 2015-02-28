#ifndef BDA_H
#define BDA_H

#include <stdint.h>
#include "btle/base.h"

namespace btle {

    /**
     * @brief The addr_type enum bluetooth address type, check from bluetooth spec for deeper understanding
     * NOTE not all platforms support this!
     */
    enum addr_type
    {
        ADDR_PUBLIC                         = 0x00,  // Public Address
        ADDR_STATIC                         = 0x01,  // Static address
        ADDR_PRIVATE_NONRESOLVE             = 0x02,  // Non-Resolvable Private Address
        ADDR_PRIVATE_RESOLVE                = 0x03   // Resolvable Private Address
    };
    #define BDA_BIN_LENGTH 6

    class bda: public base
    {
    public:
        bda();
        bda(const std::string& bda_str);
        bda(const std::string& bda_str, addr_type type);
        bda(const char bda_strc[BDA_BIN_LENGTH] , addr_type type);
        bda(const bda& other);
        ~bda();

    public: //

        addr_type type() const;

    public: // override from base

        std::string to_string() const;

    private:
        addr_type type_;
    };
}
#endif // BDA_H
