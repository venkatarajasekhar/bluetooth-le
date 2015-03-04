#ifndef SERVICE_H
#define SERVICE_H

#include "btle/base.h"
#include "btle/characteristic.h"

namespace btle {
    class service: public base{
    public:
        service();
        service(const uuid& uid);

    public:

        service& operator << (const characteristic& chr);
        service& operator << (const std::vector<characteristic>& chrs);
        bool operator == (const uuid& uid) const;
        const std::vector<characteristic>& characteristics() const;
        std::vector<characteristic>& characteristics();
        const btle::uuid& uuid() const;

    private:

        btle::uuid uuid_;
        std::vector<characteristic> characteristics_;
    };

    typedef std::vector<service>::const_iterator service_iterator_const;
    typedef std::vector<service> service_list;
}

#endif // SERVICE_H

