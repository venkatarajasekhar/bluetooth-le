
#include "btle/service.h"

using namespace btle;

service::service()
: base()
{
}

service::service(const uuid& uid)
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

bool service::operator == (const uuid& uid) const
{
    return uuid_ == uid;
}


