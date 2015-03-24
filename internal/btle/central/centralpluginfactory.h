#ifndef CENTRALPLUGINFACTORY_H
#define CENTRALPLUGINFACTORY_H

#include <vector>
#include "btle/central/centralplugininterface.h"

namespace btle {
    namespace central {
        class centralpluginfactory{
        public:

            static centralpluginfactory& instance();
            void populate(std::vector<centralplugininterface>& plugins);
            void deplete(std::vector<centralplugininterface>& plugins);
            typedef centralplugininterface* (*plugin_constructor)();
            typedef std::vector<plugin_constructor> constructors;
            void insert(plugin_constructor constructor);

        private:
            centralpluginfactory();
        };
    }
}
#endif // CENTRALPLUGINFACTORY_H

