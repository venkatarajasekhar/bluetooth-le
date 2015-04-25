
#ifndef btle_connectionhandlerlinkctrl_h
#define btle_connectionhandlerlinkctrl_h

namespace btle {
    class device;
    namespace central{
        class connectionhandlerlinkctrl{
        public:
            virtual void aquire_connect_device(btle::device& dev)=0;
            virtual void aquire_disconnect_device(btle::device& dev)=0;
            virtual void aquire_cancel_pending_connection(btle::device& dev)=0;
        };
    }
}

#endif
