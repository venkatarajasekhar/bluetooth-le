#ifndef ATTRIBUTE_NOT_NOTIFYABLE_H
#define ATTRIBUTE_NOT_NOTIFYABLE_H

#include <stdexcept>
#include <string>
#include "btle_global.h"

namespace btle {
    namespace exceptions {
        class BTLE_API attribute_not_notifyable: public std::runtime_error{
        public:
            explicit attribute_not_notifyable(const std::string& what);
            attribute_not_notifyable();
            attribute_not_notifyable(const attribute_not_notifyable& other);
        };
    }
}

#endif // ATTRIBUTE_NOT_NOTIFYABLE_H

