#include "btle/descriptor.h"

using namespace btle;

descriptor::descriptor()
{
}

descriptor::descriptor(
    uint16_t type)
: base(),
  type_(type),
  handle_(0)
{
}

descriptor::descriptor(
    uint16_t type,
    bool notifying)
: base(),
  type_(type),
  handle_(0),
  is_notifying_(notifying)
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

bool descriptor::is_notifying() const
{
    return is_notifying_;
}

void descriptor::set_notifying( bool notifying )
{
    is_notifying_ = notifying;
}

bool descriptor::operator == (const descriptor& other) const
{
    return type_ == other.type() && handle_ == other.handle();
}

void descriptor::invalidate()
{
    is_notifying_ = false;
    type_ = 0;
    handle_ = 0;
}
