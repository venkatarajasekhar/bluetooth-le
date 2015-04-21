
#ifndef btle_timer_h
#define btle_timer_h

#include "btle/timercallback.h"
#include "btle/base.h"

namespace btle {
    class timer: public base{
    public:
        timer();
        ~timer();
        
    public:
        
        void start(int ms, timercallback* callback);
        void stop();
        
    private:
        void* object_;
    };
}

#endif
