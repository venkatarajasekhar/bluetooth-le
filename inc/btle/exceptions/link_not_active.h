#ifndef LINK_NOT_ACTIVE_H
#define LINK_NOT_ACTIVE_H

#include <stdexcept>
#include <string>

namespace btle {
    namespace exceptions {
        class link_not_active: public std::runtime_error{
        public:
            explicit link_not_active(const std::string& what);
            link_not_active();
            link_not_active(const link_not_active& other);
        };
    }
}

#endif // LINK_NOT_ACTIVE_H

