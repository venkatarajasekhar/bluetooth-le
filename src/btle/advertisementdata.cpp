
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
    _value = other.string_value();
    _description = other.description();
    return *this;
}

