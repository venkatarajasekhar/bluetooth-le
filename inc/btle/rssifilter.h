#ifndef RSSIFILTER_H
#define RSSIFILTER_H

#include <vector>
#include <deque>

#include "btle_global.h"

namespace btle {
    class rssifilter{
    public:
        rssifilter();

    public: // api

        rssifilter& operator << (int rssi);
        int operator [](int index);
        int current() const;
        int median() const;
        double mean_median() const;

    private:

        std::deque<int> rssis_;
        std::deque<int> medians_;
        int median_;
        int current_;
        double mean_median_;
    };
}

#endif // RSSIFILTER_H

