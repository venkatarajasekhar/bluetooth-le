
#include "btle/service.h"

using namespace btle;

service::service()
: base()
{
}

service::service(const btle::uuid& uid)
: base(),
  uuid_(uid)
{
}

service& service::operator << (const characteristic& chr)
{
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


