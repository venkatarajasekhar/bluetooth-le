#ifndef VERSION_H
#define VERSION_H

#include <string>

namespace btle {
    class version{
    public:

        static const std::string& version_string();
        static unsigned int version_number();
    };
}

#endif // VERSION_H

