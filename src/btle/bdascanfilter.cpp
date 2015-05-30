
#include "btle/bdascanfilter.h"
#include "btle/utility.h"

using namespace btle;

bdascanfilter::bdascanfilter(const bda_list& bdas)
: scanfilterbase("BDA based scan filer bdas: " + utility::to_string((unsigned int)bdas.size())),
  bdas_(bdas)
{
}

bdascanfilter::bdascanfilter(const bdascanfilter& other)
: scanfilterbase(other),
  bdas_(other.bdas_)
{
}

bool bdascanfilter::process(device &dev, adv_fields &fields, int rssi)
{
    for( bda_list::const_iterator it = bdas_.begin(); it != bdas_.end(); ++it )
    {
        if( (*it) == dev.addr() )
        {
            return true;
        }
    }
    return false;
}



