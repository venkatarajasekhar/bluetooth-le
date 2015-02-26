#ifndef GATTSERVICEREGISTERER_H
#define GATTSERVICEREGISTERER_H

//class gattservicebase;

namespace btle {
    namespace gatt_services {
        template<typename T>
        class gattserviceregisterer
        {
        private:
            static gattservicebase* constructor();
            friend class gattservicefactory;

        public:
            gattserviceregisterer();
            ~gattserviceregisterer();
        };
    }
}

#include "btle/gatt_services/gattserviceregisterer.hpp"

#endif // GATTSERVICEREGISTERER_H

