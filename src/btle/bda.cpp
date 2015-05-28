#include "btle/bda.h"
#include "btle/utility.h"

#include <sstream>
#include <iomanip>

using namespace btle;

namespace {
    inline static const char* type2string( address_type type )
    {
        switch (type)
        {
            case btle::ADDR_PRIVATE_NONRESOLVE: return "PRIVATE_NONRESOLVE";
            case btle::ADDR_PRIVATE_RESOLVE:    return "PRIVATE_RESOLVE";
            case btle::ADDR_PUBLIC:             return "PUBLIC";
            case btle::ADDR_STATIC:             return "STATIC";
            default:                            return "UNKNOWN";
        }
    }
}

bda::bda()
: base(),
  type_(ADDR_PUBLIC)
{
}

bda::~bda()
{
}

bda::bda(const std::string& bda_str)
: base(bda_str,"BDA string: " + bda_str),
  type_(ADDR_PUBLIC)
{
}

bda::bda(const std::string& bda_str, address_type type)
: base(bda_str,"BDA string: " + bda_str + " type: " + type2string(type)),
  type_(type)
{
}

bda::bda(const char bda_strc[BDA_BIN_LENGTH] , address_type type)
: base(std::string(bda_strc,BDA_BIN_LENGTH),"BDA string: " + utility::to_hex_string((const uint8_t*)bda_strc, BDA_BIN_LENGTH) + " type: " + type2string(type)),
  type_(type)
{
}

bda::bda(const bda& other)
: base(other),
  type_(other.type())
{
}

address_type bda::type() const
{
    return type_;
}

std::string bda::to_string() const
{
    if( value_.size() == BDA_BIN_LENGTH )
    {
        std::stringstream ss_hex;
        for( int i=0; i < BDA_BIN_LENGTH; ++i )
        {
            ss_hex << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << (unsigned int)(unsigned char)value_[i] << (i < 5 ? ":" : "");
        }
        return ss_hex.str();
    }
    else return value_;
}

bool bda::operator == (const bda& other) const
{
    return value_.compare(other.string_value()) != std::string::npos;
}

