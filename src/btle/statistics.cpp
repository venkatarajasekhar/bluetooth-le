
#include "btle/statistics.h"

using namespace btle;

statistics::statistics()
: base("","Statistics class"),
  connection_state_stats_()
{
}

statistics& statistics::operator << (const connection_stat_pair& pair)
{
    connection_state_stats_.push_back(pair);
    return *this;
}

const std::vector<connection_stat_pair>& statistics::connection_state_stats() const
{
    return connection_state_stats_;
}

void statistics::invalidate()
{
    connection_state_stats_.clear();
}


