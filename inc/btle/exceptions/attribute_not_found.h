#ifndef ATTRIBUTE_NOT_FOUND_H
#define ATTRIBUTE_NOT_FOUND_H

#include <stdexcept>
#include <string>
#include "btle_global.h"

namespace btle {
    namespace exceptions {
        class BTLE_API attribute_not_found: public std::runtime_error{
        public:
            explicit attribute_not_found(const std::string& what);
            attribute_not_found();
            attribute_not_found(const attribute_not_found& other);
        };
    }
}

#endif // ATTRIBUTE_NOT_FOUND_H

