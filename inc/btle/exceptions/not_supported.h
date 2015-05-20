#ifndef NOT_SUPPORTED_H
#define NOT_SUPPORTED_H

#include <stdexcept>
#include <string>
#include "btle_global.h"

namespace btle {
    namespace exceptions {
        class BTLE_API not_supported: public std::runtime_error{
        public:
            explicit not_supported(const std::string& what);
            not_supported();
            not_supported(const not_supported& other);
        };
    }
}

#endif // NOT_SUPPORTED_H

