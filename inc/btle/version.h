#ifndef VERSION_H
#define VERSION_H

#include <string>
#include "btle_global.h"

namespace btle {
    class BTLE_API version{
    public:

        static const std::string& version_string();
        static unsigned int version_number();
    };
}

#endif // VERSION_H

