#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include "btle_global.h"

namespace btle {
    /**
     * @brief The utility class, common conversion utility until we start using c++ 11 features
     */
    class BTLE_API utility{
    public:
        static std::string to_string(int value);
        static std::string to_string(unsigned int value);
        static std::string to_string(double value);
        static std::string to_hex_string(const uint8_t* data, size_t size,const char* separator=" ");
        static std::string to_hex_string(const std::string& data,const char* separator=" ");
        static int to_int(const std::string& data);
        static unsigned int to_uint(const std::string& data);
    };
}

#endif // UTILITY_H

