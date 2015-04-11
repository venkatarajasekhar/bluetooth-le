
#include "btle/gattdatabase.h"

using namespace btle;

gattdatabase::gattdatabase()
: base(),
  services_()
{
}

gattdatabase& gattdatabase::operator << (const service& srv)
{
    for (service_iterator_const it = services_.begin(); it != services_.end(); ++it) {
        if( (*it) == srv ){
            return *this;
        }
    }
    services_.push_back(srv);
    return *this;
}

gattdatabase& gattdatabase::operator << (const service_list& services)
{
    services_ = services;
    return *this;
}

std::vector<service>& gattdatabase::services()
{
    return services_;
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

