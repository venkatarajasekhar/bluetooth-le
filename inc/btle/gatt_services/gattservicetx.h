#ifndef GATTSERVICETX_H
#define GATTSERVICETX_H

#include <string>

namespace btle {
    class device;
    namespace gatt_services {
        /**
         * @brief The gattservicetx class, abstract callback class for sending e.g. simple
         *                                 control point message etc...
         */
        class gattservicetx{
        public:
            virtual void write_value(const std::string& msg, device& dev) = 0;
        };
    }
}

#endif // GATTSERVICETX_H

