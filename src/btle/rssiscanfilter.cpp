
#include "btle/rssiscanfilter.h"
#include "btle/utility.h"

using namespace btle;

rssiscanfilter::rssiscanfilter(int rssi_limit)
: scanfilterbase("RSSI based scan filer limit set to: " + utility::to_string(rssi_limit)),
  rssi_limit_(rssi_limit)
{
}

rssiscanfilter::rssiscanfilter(const rssiscanfilter& other)
: scanfilterbase(other),
  rssi_limit_(other.rssi_limit_)
{
}

bool rssiscanfilter::process(device &dev, adv_fields &fields, int rssi)
{
    return dev.rssi_filter().mean_median() >= rssi_limit_;
}



