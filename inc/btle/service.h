#ifndef SERVICE_H
#define SERVICE_H

#include "btle/base.h"
#include "btle/characteristic.h"

namespace btle {
    class service: public base{
    public:
        service();
        service(const uuid& uid);

        service& operator << (const characteristic& chr);
        service& operator << (const std::vector<characteristic>& chrs);
        bool operator == (const uuid& uid) const;

    private:

        uuid uuid_;
        std::vector<characteristic> characteristics_;
    };
}

#endif // SERVICE_H

