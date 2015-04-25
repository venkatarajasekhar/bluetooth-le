#ifndef GATTSERVICEBASE_H
#define GATTSERVICEBASE_H

#include "btle/base.h"
#include "btle/uuid.h"
#include "btle/error.h"

namespace btle {
    namespace gatt_services {
        class BTLE_API gattservicebase: public base{
        public:
            gattservicebase();
            virtual ~gattservicebase();

        public:

            /**
             * @brief process_service_data, gatt service must implement gatt service processing
             * for all included characteristics
             * @param chr
             * @param data
             * @param size
             */
            virtual void process_service_notify_data(const uuid& chr, const uint8_t* data, size_t size) = 0;

            virtual void process_service_value_read(const uuid& chr, const uint8_t* data, size_t size, const error& err) = 0;

            /**
             * @brief reset, informs gatt service to reset it's values,
             *               typically after device has been disconnected
             */
            virtual void reset() = 0;
            virtual int write_service_value(const uuid& chr, const std::string& data);
            virtual void set_active(const uuid& uid, bool notifying);
            virtual bool is_active() const;
            virtual std::string json(const uuid& uid) const;

        public:

            const uuid_list& included_characteristics() const;
            const uuid_list& mandatory_notifications() const;
            bool  contains_characteristic_uuid(const uuid& uid) const;
            const uuid& service_uuid() const;

        protected:

            uuid_list included_characteristics_;
            uuid_list mandatory_notifications_;
            uuid service_;
        };

        typedef std::vector<gattservicebase*> gatt_service_list;
        typedef std::vector<gattservicebase*>::iterator gatt_service_iterator;
        typedef std::vector<gattservicebase*>::const_iterator gatt_service_iterator_const;
    }
}

#endif // GATTSERVICEBASE_H

