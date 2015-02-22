#ifndef ADVERTISEMENTDATA_H
#define ADVERTISEMENTDATA_H

#include <string>
#include "btle/base.h"

namespace btle{
    class advertisementdata: public base
    {
    public:
        advertisementdata();
        advertisementdata(const std::string& data);
        advertisementdata( const advertisementdata& other );
        advertisementdata& operator = (const advertisementdata& other);
    };
}

#endif // ADVERTISEMENTDATA_H

