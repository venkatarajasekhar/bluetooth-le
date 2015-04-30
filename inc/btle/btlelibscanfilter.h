#ifndef BTLELIBSCANFILTER_H
#define BTLELIBSCANFILTER_H

#include "btle/scanfilterbase.h"

namespace btle {
    /**
     * @brief The btlelibscanfilter class,
     */
    class BTLE_API btlelibscanfilter: public scanfilterbase{
    public:
        btlelibscanfilter();
        btlelibscanfilter(const btlelibscanfilter& other);

    public:// from base
        bool process(device &dev,adv_fields& fields,int rssi);

    };
}

#endif // BTLELIBSCANFILTER_H

