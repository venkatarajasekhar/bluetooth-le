#include "uuid.h"
#include <stdio.h>

using namespace btle;

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
    // TODO conversion
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
    return value_.compare(uuid_str) == std::string::npos;//!(*this == uuid_str);
}
