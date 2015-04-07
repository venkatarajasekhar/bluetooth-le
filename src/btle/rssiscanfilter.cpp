
#include "btle/rssiscanfilter.h"

using namespace btle;

rssiscanfilter::rssiscanfilter(int rssi_limit)
: scanfilterbase("BDA based scan filer"),
  rssi_limit_(rssi_limit)
{
}

rssiscanfilter::rssiscanfilter(const rssiscanfilter& other)
: scanfilterbase(other),
  rssi_limit_(other.rssi_limit_)
{
}

bool rssiscanfilter::process(device &dev)
{
    return dev.rssi_filter().mean_median() >= rssi_limit_;
}



