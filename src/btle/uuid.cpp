#include "btle/uuid.h"
#include "btle/utility.h"

#include <stdio.h>
#include <sstream>
#include <iomanip>
#include <assert.h>

using namespace btle;

namespace {
    #define UUID_16BIT_128_POST_FIX "-0000-1000-8000-00805f9b34fb"
    #define UUID_16_128_FOMAT_LEN 36
}

uuid::uuid()
: base()
{
}

uuid::uuid(const uuid& other)
: base(other),
  uuid16_(other.uuid16_)
{
}

uuid::uuid(uint16_t uuid16)
: base(),
  uuid16_(uuid16)
{
}

uuid::uuid(const std::string& uuid_str)
: base(uuid_str),
  uuid16_(0)
{
    switch(uuid_str.size())
    {
        case 2:
        {
            memcpy(&uuid16_,uuid_str.c_str(),sizeof(uuid16_));
            //value_ = "";
            break;
        }
        case 4:
        {
            std::stringstream ss;
            ss << std::hex << uuid_str;
            ss >> uuid16_;
            //value_ = "";
            break;
        }
        case 16:
        case 32:
            break;
        case UUID_16_128_FOMAT_LEN:
        {
            std::string::size_type pos(uuid_str.find(UUID_16BIT_128_POST_FIX,
                                       sizeof(UUID_16BIT_128_POST_FIX)));
            if( pos != std::string::npos ){
                std::string uuid_16( uuid_str.substr(pos - 5,4) );
                std::stringstream ss;
                ss << std::hex << uuid_16;
                ss >> uuid16_;
                //value_ = "";
            }
            break;
        }
        default:
        {
            assert(false);
            break;
        }
    }
}

uuid::uuid(const uint8_t uuid128[UUID_128_BIN_LENGTH])
: base(std::string((const char*)uuid128,UUID_128_BIN_LENGTH)),
  uuid16_(0)
{
}

uint16_t uuid::uuid16bit() const
{
    return uuid16_;
}

const std::string& uuid::uuid128bit() const
{
    return value_;
}

bool uuid::is16bit() const
{
    return uuid16_ != 0;
}

bool uuid::is128bit() const
{
    return value_.size() != 0;
}

bool uuid::operator == (const uuid& other) const
{
    return is16bit() ? *this == other.uuid16bit() : *this == other.uuid128bit();
}

bool uuid::operator == (uint16_t uuid16) const
{
    return uuid16_ == uuid16;
}

bool uuid::operator == (const uint8_t uuid128[UUID_128_BIN_LENGTH]) const
{
    return value_.compare(std::string((const char*)uuid128,UUID_128_BIN_LENGTH)) != std::string::npos;
}

bool uuid::operator == (const std::string& uuid_str) const
{
    return value_.compare(uuid_str) != std::string::npos;
}

bool uuid::operator != (const uuid& other) const
{
    return !(*this == other);
}

bool uuid::operator != (uint16_t uuid16) const
{
    return !(*this == uuid16);
}

bool uuid::operator != (const uint8_t uuid128[UUID_128_BIN_LENGTH]) const
{
    return !(*this == uuid128);
}

bool uuid::operator != (const std::string& uuid_str) const
{
    return value_.compare(uuid_str) == std::string::npos;
}

std::string uuid::to_string() const
{
    if( uuid16_ != 0 )
    {
        return utility::to_hex_string((const uint8_t*)&uuid16_,2,NULL);
    }
    else return value_;
}

