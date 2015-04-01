#ifndef CENTRALPLUGINREGISTERER_H
#define CENTRALPLUGINREGISTERER_H

namespace btle {
    namespace central {

        class centralpluginobserver;

        template<typename T>
        class centralpluginregisterer{
        public:
            static centralplugininterface* constructor(centralpluginobserver& observer);
            friend class centralpluginfactory;

            centralpluginregisterer();
            ~centralpluginregisterer();

        };
    }
}
#include "centralpluginregisterer.hpp"

#endif

