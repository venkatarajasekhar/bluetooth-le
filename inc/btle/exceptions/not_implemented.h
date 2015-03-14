#ifndef NOT_IMPLEMENTED_H
#define NOT_IMPLEMENTED_H

#include <stdexcept>
#include <string>
#include "btle_global.h"

namespace btle {
    namespace exceptions {
        class BTLE_API not_implemented: public std::runtime_error{
        public:
            explicit not_implemented(const std::string& what);
            not_implemented();
            not_implemented(const not_implemented& other);
        };
    }
}

#endif // NOT_IMPLEMENTED_H

