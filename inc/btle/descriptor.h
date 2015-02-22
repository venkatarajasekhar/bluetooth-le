#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include "btle/base.h"

namespace btle {

    #define CHARACTERISTIC_EXTENDED_PROPERTIES   0x2900
    #define CHARACTERISTIC_USER_DESCRIPTION      0x2901
    #define CLIENT_CHARACTERISTIC_CONFIGURATION  0x2902
    #define SERVER_CHARACTERISTIC_CONFIGURATION  0x2903
    #define CHARACTERISTIC_FORMAT                0x2904
    #define CHARACTERISTIC_AGGREGATE_FORMAT      0x2905

    class descriptor
    {
    public:
        descriptor();
        ~descriptor();
    };
}

#endif // DESCRIPTOR_H
