#ifndef STATISTICS_H
#define STATISTICS_H

#include "btle/base.h"

#include <vector>

namespace btle {

    /**
     * @brief connection_stat_pair,
     *        first = connection state,
     *        second = time stamp
     */
    typedef std::pair<int,std::string> connection_stat_pair;

    /**
     * @brief The statistics class statistics class,
     *        to store important device related stats,
     *        this class will be extented in future releases
     */
    class statistics: public base{
    public:

        statistics();

    public:

        statistics& operator << (const connection_stat_pair& pair);
        const std::vector<connection_stat_pair>& connection_state_stats() const;

    public: // from base

        void invalidate();

    private:

        std::vector<connection_stat_pair> connection_state_stats_;
    };
}

#endif // STATISTICS_H

