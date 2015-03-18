#ifndef VERIFY_H
#define VERIFY_H

#include <assert.h>

namespace btle {
    #ifdef NDEBUG
        #define verify(a) assert(a);
    #else
        #define verify(a)
    #endif
}

#endif // VERIFY_H

