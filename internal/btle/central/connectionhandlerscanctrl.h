
#ifndef btle_connectionhandlerscanctrl_h
#define btle_connectionhandlerscanctrl_h

namespace btle {
    namespace central{
        class connectionhandlerscanctrl{
        public:
            virtual void aquire_start_scan()=0;
            virtual void aquire_stop_scan()=0;
        };
    }
}

#endif
