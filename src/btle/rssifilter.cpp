
#include "btle/rssifilter.h"
#include <algorithm>

using namespace btle;

namespace {
    #define RSSI_MEDIAN_LIMIT 7
}

rssifilter::rssifilter()
: rssis_(),
  medians_(),
  median_(-100),
  current_(-100),
  mean_median_(-100.0)
{
}

rssifilter& rssifilter::operator << (int rssi)
{
    if( rssi < 0 )
    {
        current_ = rssi;
        rssis_.push_back(rssi);
        if( rssis_.size() >= RSSI_MEDIAN_LIMIT )
        {
            if( rssis_.size() > RSSI_MEDIAN_LIMIT ) rssis_.pop_front();
            rssis_sorted_ = rssis_;
            std::sort(rssis_sorted_.begin(),rssis_sorted_.end());
            median_ = rssis_sorted_[3];
            medians_.push_back(median_);
            if( medians_.size() >= 2 )
            {
                if( medians_.size() > 2 ) medians_.pop_front();
                int msize( (int)medians_.size() );
                mean_median_ = (medians_[msize-1] + medians_[msize-2])/2.0;
            }
            else
            {
                mean_median_ = median_;
            }
        }
        else
        {
            median_      = rssi;
            mean_median_ = (double)rssi;
        }
    }
    return *this;
}

int rssifilter::operator [](int index)
{
    return rssis_[index];
}

int rssifilter::current() const
{
    return current_;
}

int rssifilter::median() const
{
    return median_;
}

double rssifilter::mean_median() const
{
    return mean_median_;
}
