#ifndef LINK_NOT_ACTIVE_H
#define LINK_NOT_ACTIVE_H

#include <stdexcept>
#include <string>
#include "btle_global.h"

namespace btle {
    namespace exceptions {
        class BTLE_API link_not_active: public std::runtime_error{
        public:
            explicit link_not_active(const std::string& what);
            link_not_active();
            link_not_active(const link_not_active& other);
        };
    }
}

#endif // LINK_NOT_ACTIVE_H

