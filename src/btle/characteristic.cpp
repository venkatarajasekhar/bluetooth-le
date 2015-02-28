#include "characteristic.h"

using namespace btle;

characteristic::characteristic()
: base()
{
}

characteristic::characteristic(
    const std::string& data,
    const btle::uuid& uid)
: base(data),
  uuid_(uid)
{
}

characteristic::characteristic(
    const btle::uuid& uid)
: base(),
  uuid_(uid)
{
}

characteristic::characteristic(
    const btle::uuid& uid,
    uint8_t properties)
: base(),
  uuid_(uid),
  characteristic_properties_(properties)
{
}

characteristic::characteristic(
    const btle::uuid& uid,
    uint8_t properties,
    uint16_t attribute_handle,
    uint16_t characteristic_properties)
: base(),
  uuid_(uid),
  characteristic_properties_(properties),
  attribute_handle_(attribute_handle)
{
}

characteristic::characteristic(const characteristic& other)
: base(other)
{
}

uint8_t characteristic::properties() const
{
    return characteristic_properties_;
}

const uuid& characteristic::uuid() const
{
    return uuid_;
}

characteristic& characteristic::operator << (const descriptor& desc)
{
    // TODO add check for allready containing desc!
    descriptors_.push_back(desc);
    return *this;
}

bool characteristic::contains_descriptor_type(uint16_t type) const
{
    for( std::vector<descriptor>::const_iterator it = descriptors_.begin(); it != descriptors_.end(); ++it )
    {
        if( it->type() == type )
        {
            return true;
        }
    }
    return false;
}

