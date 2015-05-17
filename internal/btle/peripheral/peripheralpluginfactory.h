#ifndef PERIPHERALPLUGINFACTORY_H
#define PERIPHERALPLUGINFACTORY_H

#include <vector>
#include "btle/peripheral/peripheralplugininterface.h"

namespace btle {
    namespace peripheral {

        class peripheralpluginfactory{
        public:

            static peripheralpluginfactory& instance();
            void populate(std::vector<peripheralplugininterface*> &plugins,
                          peripheralpluginobserver& observer);
            void deplete(std::vector<peripheralplugininterface*>& plugins);
            typedef peripheralplugininterface* (*plugin_constructor)(peripheralpluginobserver& observer);
            typedef std::vector<plugin_constructor> constructors;
            void insert(plugin_constructor constructor);

        private:
            peripheralpluginfactory();
            constructors constructors_;
        };
    }
}

#endif // PERIPHERALPLUGINFACTORY_H

