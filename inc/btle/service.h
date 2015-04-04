#ifndef SERVICE_H
#define SERVICE_H

#include "btle/base.h"
#include "btle/characteristic.h"

namespace btle {
    class BTLE_API service: public base{
    public:
        service();
        service(const uuid& uid);
        service(const uuid& uid,
                long int instance_id);
        service(const uuid &uid,
                uint16_t start_handle,
                uint16_t end_handle);
        service(const service& other);

    public:

        service& operator << (const characteristic& chr);
        service& operator << (const std::vector<characteristic>& chrs);
        bool operator == (const btle::uuid& uid) const;
        bool operator == (const service& other) const;
        const characteristic &operator [](int index) const;
        
        const std::vector<characteristic>& characteristics() const;
        std::vector<characteristic>& characteristics();
        
        const btle::uuid& uuid() const;
        uint16_t start_handle() const;
        uint16_t end_handle() const;
        long int instance_id() const;
        
    private:

        btle::uuid uuid_;
        std::vector<characteristic> characteristics_;
        uint16_t start_handle_;
        uint16_t end_handle_;
        long int instance_id_;
    };

    typedef std::vector<service>::iterator service_iterator;
    typedef std::vector<service>::const_iterator service_iterator_const;
    typedef std::vector<service> service_list;
}

#endif // SERVICE_H

