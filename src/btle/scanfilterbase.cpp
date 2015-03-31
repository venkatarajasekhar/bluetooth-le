
#include "btle/scanfilterbase.h"

using namespace btle;

scanfilterbase::scanfilterbase()
: base()
{
}

scanfilterbase::scanfilterbase(const std::string& description)
: base("",description)
{
}

scanfilterbase::scanfilterbase(const scanfilterbase& other)
: base(other)
{
}

