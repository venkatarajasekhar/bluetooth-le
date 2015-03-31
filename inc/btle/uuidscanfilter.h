#ifndef UUIDSCANFILTER_H
#define UUIDSCANFILTER_H

#include "btle/scanfilterbase.h"

namespace btle {
    class BTLE_API uuidscanfilter: public scanfilterbase{
    public:
        uuidscanfilter(const uuid_list& uuids);
        uuidscanfilter(const uuidscanfilter& other);

    public:// from base
        bool process(device &dev);

    private:
        uuid_list uuids_;
    };
}

#endif // UUIDSCANFILTER_H

