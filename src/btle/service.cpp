
#include "btle/service.h"

using namespace btle;

service::service()
: base(),
  uuid_(),
  characteristics_(),
  start_handle_(0),
  end_handle_(0)

{
}

service::service(const btle::uuid& uid)
: base(),
  uuid_(uid),
  characteristics_(),
  start_handle_(0),
  end_handle_(0)
{
}

service::service(
    const btle::uuid& uid,
    uint16_t start_handle,
    uint16_t end_handle)
: base(),
  uuid_(uid),
  characteristics_(),
  start_handle_(start_handle),
  end_handle_(end_handle)
{
}

service& service::operator << (const characteristic& chr)
{
    // TODO check does characteristic allready exist
    characteristics_.push_back(chr);
    return *this;
}

service& service::operator << (const std::vector<characteristic>& chrs)
{
    characteristics_ = chrs;
    return *this;
}

bool service::operator == (const btle::uuid& uid) const
{
    return uuid_ == uid;
}

const std::vector<characteristic>& service::characteristics() const
{
    return characteristics_;
}

std::vector<characteristic>& service::characteristics()
{
    return characteristics_;
}

const btle::uuid& service::uuid() const
{
    return uuid_;
}


