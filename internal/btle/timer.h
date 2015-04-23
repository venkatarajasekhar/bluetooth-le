
#ifndef btle_timer_h
#define btle_timer_h

#include "btle/timercallback.h"
#include "btle/base.h"

namespace btle {
    /**
     * simple timer class for lib internal usage
     * for some reason in mac/ios posix itimerval does not work so that why there is timer implementation per platform
     * for ios/mac timer_darwin for windows timer_win32 and for linux timer_posix
     */
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
