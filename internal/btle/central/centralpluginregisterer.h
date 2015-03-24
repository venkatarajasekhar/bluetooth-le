#ifndef CENTRALPLUGINREGISTERER_H
#define CENTRALPLUGINREGISTERER_H

namespace btle {
    namespace central {
        template<typename T>
        class centralpluginregisterer{
        public:
            static centralplugininterface* constructor();
            friend class centralpluginfactory;

            centralpluginregisterer();
            ~centralpluginregisterer();

        };
    }
}
#include "centralpluginregisterer.hpp"

#endif // CENTRALPLUGINREGISTERER_H

