#ifndef GATTSERVICEFACTORY_H
#define GATTSERVICEFACTORY_H

#include <set>
#include <vector>

#include "btle/gatt_services/gattservicebase.h"

namespace btle {
    namespace gatt_services {
        class BTLE_API gattservicefactory{
        public:

            static gattservicefactory& instance();

        public:

            void populate(std::vector<gattservicebase*>& services);
            void deplete(std::vector<gattservicebase*>& services);

        private:
            typedef gattservicebase* (*service_constructor)();
            typedef std::set<service_constructor> constructors;

        private:
            gattservicefactory();
        public:
            void insert(service_constructor constructor);

        private:
            constructors constructors_;
        };
    }
}

#endif // GATTSERVICEFACTORY_H

