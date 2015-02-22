#include "bda.h"

#include <sstream>
#include <iomanip>

btle::bda::bda()
: base(),
  _type(ADDR_PUBLIC)
{
}

btle::bda::~bda()
{
}

btle::bda::bda(const std::string& bda_str)
: base(bda_str,"")
{
}

btle::bda::bda(const std::string& bda_str, addr_type type)
: base(bda_str,""),
  _type(type)
{
}

btle::bda::bda(const char bda_strc[kNativeAddrMaxLen] , addr_type type)
: base(std::string(bda_strc,btle::kNativeAddrMaxLen),""),
  _type(type)
{
}

btle::bda::bda(const btle::bda& other)
: base(other.string_value(),""),
  _type(other.type())
{
}

btle::addr_type btle::bda::type() const
{
    return _type;
}

std::string btle::bda::to_string() const
{
    if( _value.size() == kNativeAddrMaxLen )
    {
        std::stringstream ss_hex;
        for( int i=0; i < kNativeAddrMaxLen; ++i )
        {
            ss_hex << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << (unsigned int)(unsigned char)_value[i] << (i < 5 ? ":" : "");
        }
        return ss_hex.str();
    }
    else return _value;
}
