#ifndef RSSISCANFILTER_H
#define RSSISCANFILTER_H

#include "btle/scanfilterbase.h"

namespace btle {
    class BTLE_API rssiscanfilter: public scanfilterbase{
    public:
        rssiscanfilter(int rssi_limit);
        rssiscanfilter(const rssiscanfilter& other);

    public:// from base
        bool process(device &dev);

    private:
        int rssi_limit_;
    };
}

#endif // RSSISCANFILTER_H

