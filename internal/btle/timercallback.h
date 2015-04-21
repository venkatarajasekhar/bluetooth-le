
#ifndef btle_timercallback_h
#define btle_timercallback_h

namespace btle {
    class timer;
    class timercallback{
    public:
        virtual void timer_expired(timer* t) = 0;
    };
}

#endif
