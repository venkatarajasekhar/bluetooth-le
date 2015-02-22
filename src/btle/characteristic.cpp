#include "characteristic.h"

using namespace btle;

characteristic::characteristic()
: base()
{
}

characteristic::characteristic(const std::string& data)
: base(data,"")
{
}

characteristic::characteristic(const characteristic& other)
: base(other)
{
}

characteristic::~characteristic()
{
}

