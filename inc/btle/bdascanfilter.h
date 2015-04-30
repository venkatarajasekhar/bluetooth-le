#ifndef BDASCANFILTER_H
#define BDASCANFILTER_H

#include "btle/scanfilterbase.h"

namespace btle {
    class BTLE_API bdascanfilter: public scanfilterbase{
    public:
        bdascanfilter(const bda_list& bdas);
        bdascanfilter(const bdascanfilter& other);

    public:// from base
        bool process(device &dev,adv_fields& fields,int rssi);

    private:
        bda_list bdas_;
    };
}

#endif // BDASCANFILTER_H

