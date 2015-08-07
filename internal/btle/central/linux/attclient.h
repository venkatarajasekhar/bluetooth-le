#ifndef ATTCLIENT_H
#define ATTCLIENT_H

#include "btle_global.h"
#include <string>

namespace btle {
    namespace central {
        namespace linux_platform {
            class attclient{
            public:
                attclient();

            public:

                void read_by_group_type(uint16_t start, uint16_t end);

            private:

                void request(int opcode, std::string& data);
            };
        }
    }
}

#endif // ATTCLIENT_H

