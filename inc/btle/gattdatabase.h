#ifndef GATTDATABASE_H
#define GATTDATABASE_H

#include "btle/base.h"
#include "btle/service.h"

namespace btle {
    class BTLE_API gattdatabase: public base {
    public:
        gattdatabase();

    public: // api

        gattdatabase& operator << (const service& srv);
        gattdatabase& operator << (const service_list& services);

    public: // api

        const characteristic* fetch_characteristic(const uuid& uid) const;
        const characteristic* fetch_characteristic(const uuid_pair& pair) const;

        const service* fetch_service(const uuid& uid) const;
        const service* fetch_service_by_chr_uuid(const uuid& uid) const;

    private:

        std::vector<service> services_;
    };
}

#endif // GATTDATABASE_H

