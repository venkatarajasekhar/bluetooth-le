
#include "btle/bdascanfilter.h"

using namespace btle;

bdascanfilter::bdascanfilter(const bda_list& bdas)
: scanfilterbase("BDA based scan filer"),
  bdas_(bdas)
{
}

bdascanfilter::bdascanfilter(const bdascanfilter& other)
: scanfilterbase(other),
  bdas_(other.bdas_)
{
}

bool bdascanfilter::process(device &dev)
{
    for( bda_iterator_const it = bdas_.begin(); it != bdas_.end(); ++it )
    {
        if( (*it) == dev.addr() )
        {
            return true;
        }
    }
    return false;
}



