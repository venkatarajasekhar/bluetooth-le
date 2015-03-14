#ifndef GATTSERVICEBASE_H
#define GATTSERVICEBASE_H

#include "btle/base.h"
#include "btle/uuid.h"

namespace btle {
    namespace gatt_services {
        class BTLE_API gattservicebase: public base{
        public:
            gattservicebase();

        public:

            virtual void process_service_data(const uuid& chr, const uint8_t* data, size_t size) = 0;

            const uuid_list& included_characteristics() const;
            const uuid_list& mandatory_notifications() const;

        protected:

            uuid_list included_characteristics_;
            uuid_list mandatory_notifications_;
            uuid service_;
        };

        typedef std::vector<gattservicebase*> gatt_list;
    }
}

#endif // GATTSERVICEBASE_H

