#ifndef ATTRIBUTE_NOT_WRITABLE_H
#define ATTRIBUTE_NOT_WRITABLE_H

#include <stdexcept>
#include <string>
#include "btle_global.h"

namespace btle {
    namespace exceptions {
        class BTLE_API attribute_not_writable: public std::runtime_error{
        public:
            explicit attribute_not_writable(const std::string& what);
            attribute_not_writable();
            attribute_not_writable(const attribute_not_writable& other);
        };
    }
}

#endif // ATTRIBUTE_NOT_WRITABLE_H

