#ifndef PERIPHERALPLUGINREGISTERER_H
#define PERIPHERALPLUGINREGISTERER_H

namespace btle {
    namespace peripheral {

        class peripheralpluginobserver;

        template<typename T>
        class peripheralpluginregisterer{
        public:
            static peripheralplugininterface* constructor(peripheralpluginobserver& observer);
            friend class centralpluginfactory;

            peripheralpluginregisterer();
            ~peripheralpluginregisterer();

        };
    }
}
#include "peripheralpluginregisterer.hpp"

#endif // PERIPHERALPLUGINREGISTERER_H

