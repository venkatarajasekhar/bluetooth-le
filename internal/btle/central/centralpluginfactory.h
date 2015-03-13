#ifndef CENTRALPLUGINFACTORY_H
#define CENTRALPLUGINFACTORY_H

#include <vector>

class centralplugininterface;

namespace btle {
    namespace central {
        class centralpluginfactory{
        public:

            centralpluginfactory& instance();
            void populate(std::vector<centralplugininterface>& plugins);
            void deplete(std::vector<centralplugininterface>& plugins);

        private:

            centralpluginfactory();
        };
    }
}
#endif // CENTRALPLUGINFACTORY_H

