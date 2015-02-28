#include "btle/descriptor.h"

using namespace btle;

descriptor::descriptor()
{
}

descriptor::descriptor(
    uint16_t type)
: base(),
  type_(type)
{
}

descriptor::descriptor(
    uint16_t type,
    uint16_t handle)
: base(),
  type_(type),
  handle_(handle)
{
}

descriptor::descriptor(const descriptor& other)
: base(other),
  type_(other.type_),
  handle_(other.handle_)
{
}

uint16_t descriptor::type() const
{
    return type_;
}

uint16_t descriptor::handle() const
{
    return handle_;
}


