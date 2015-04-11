#include "bda.h"

#include <sstream>
#include <iomanip>

using namespace btle;

bda::bda()
: base(),
  type_(ADDR_PUBLIC)
{
}

bda::~bda()
{
}

bda::bda(const std::string& bda_str)
: base(bda_str,"")
{
}

bda::bda(const std::string& bda_str, address_type type)
: base(bda_str,""),
  type_(type)
{
}

bda::bda(const char bda_strc[BDA_BIN_LENGTH] , address_type type)
: base(std::string(bda_strc,BDA_BIN_LENGTH),""),
  type_(type)
{
}

bda::bda(const bda& other)
: base(other.string_value(),""),
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

