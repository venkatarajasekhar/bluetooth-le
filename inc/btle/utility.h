#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include "btle_global.h"

namespace btle {
    class BTLE_API utility{
    public:
        static std::string to_string(int value);
        static std::string to_string(unsigned int value);
        static std::string to_hex_string(const uint8_t* data, size_t size, char separator=' ');
        static std::string to_hex_string(const std::string& data, char separator=' ');
        static int to_int(const std::string& data);
        static unsigned int to_uint(const std::string& data);
    };
}

#endif // UTILITY_H

