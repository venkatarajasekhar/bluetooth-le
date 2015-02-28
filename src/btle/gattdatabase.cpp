
#include "btle/gattdatabase.h"

using namespace btle;

gattdatabase::gattdatabase()
: base(),
  services_()
{
}

gattdatabase& gattdatabase::operator << (const service& srv)
{
    services_.push_back(srv);
    return *this;
}
