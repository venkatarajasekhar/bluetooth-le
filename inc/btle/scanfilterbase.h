#ifndef SCANFILTERBASE_H
#define SCANFILTERBASE_H

#include "btle/base.h"
#include "btle/device.h"

namespace btle {
    class BTLE_API scanfilterbase: public base
    {
    public:
        scanfilterbase();
        scanfilterbase(const std::string& description);
        scanfilterbase(const scanfilterbase& other);

        /**
         * @brief process
         * @param dev
         * @return true if device discovered callback is needed, this means no further filters are called
         */
        virtual bool process(device& dev)=0;
    };

    typedef std::vector<scanfilterbase*> scan_filters;
}

#endif // SCANFILTERBASE_H

