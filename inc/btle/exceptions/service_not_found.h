#ifndef SERVICE_NOT_FOUND_H
#define SERVICE_NOT_FOUND_H

#include <stdexcept>
#include <string>

namespace btle {
    namespace exceptions {
        class service_not_found: public std::runtime_error{
        public:
            explicit service_not_found(const std::string& what);
            service_not_found();
            service_not_found(const service_not_found& other);
        };
    }
}

#endif // SERVICE_NOT_FOUND_H

