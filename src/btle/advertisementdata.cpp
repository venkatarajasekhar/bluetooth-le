
#include "advertisementdata.h"

using namespace btle;

advertisementdata::advertisementdata()
{
}

advertisementdata::advertisementdata(const std::string& data)
: base(data,"")
{
}

advertisementdata::advertisementdata( const advertisementdata& other )
: base(other)
{
}

advertisementdata& advertisementdata::operator = (const advertisementdata& other)
{
    value_ = other.string_value();
    description_ = other.description();
    return *this;
}

