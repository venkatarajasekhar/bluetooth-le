#ifndef COLLECTOR_H
#define COLLECTOR_H

#include "btle/uuid.h"

namespace btle {
    namespace central {
        /**
         * @brief The collector class, main interface class for lib central usage
         */
        class collector{
        public:

            collector();

        public:

            void set_scan_filter(const std::vector<uuid>& filter);
            void set_scan_filter(const uuid& uid);
            void start_scan();
            void stop_scan();

        private:

            std::vector<uuid> filter_;
        };
    }
}

#endif // COLLECTOR_H

