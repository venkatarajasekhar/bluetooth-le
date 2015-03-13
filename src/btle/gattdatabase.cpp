
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

const characteristic* gattdatabase::fetch_characteristic(const uuid& uid) const
{
    for( std::vector<service>::const_iterator it_srv = services_.begin(); it_srv != services_.end(); ++it_srv )
    {
        for(chr_iterator_const it_chr = it_srv->characteristics().begin(); it_chr != it_srv->characteristics().end(); ++it_chr )
        {
            if(it_chr->uuid() == uid)
            {
                return (const characteristic*)&(*it_chr);
            }
        }
    }
    return NULL;
}

const characteristic* gattdatabase::fetch_characteristic(const uuid_pair& pair) const
{
    for( std::vector<service>::const_iterator it_srv = services_.begin(); it_srv != services_.end(); ++it_srv )
    {
        if(it_srv->uuid() == pair.first)
        {
            for(chr_iterator_const it_chr = it_srv->characteristics().begin(); it_chr != it_srv->characteristics().end(); ++it_chr )
            {
                if(it_chr->uuid() == pair.second)
                {
                    return (const characteristic*)&(*it_chr);
                }
            }
        }
    }
    return NULL;
}

const service* gattdatabase::fetch_service(const uuid& uid) const
{
    for( std::vector<service>::const_iterator it_srv = services_.begin(); it_srv != services_.end(); ++it_srv )
    {
        if(it_srv->uuid() == uid)
        {
            return (const service*)&(*it_srv);
        }
    }
    return NULL;
}

const service* gattdatabase::fetch_service_by_chr_uuid(const uuid& uid) const
{
    for( std::vector<service>::const_iterator it_srv = services_.begin(); it_srv != services_.end(); ++it_srv )
    {
        for(chr_iterator_const it_chr = it_srv->characteristics().begin(); it_chr != it_srv->characteristics().end(); ++it_chr )
        {
            if(it_chr->uuid() == uid)
            {
                return (const service*)&(*it_srv);
            }
        }
    }
    return NULL;
}

