#ifndef PERIPHERALPLUGINOBSERVER_H
#define PERIPHERALPLUGINOBSERVER_H

namespace btle {
    class error;
    class service;
    class device;
    namespace peripheral {
        class peripheralpluginobserver{
        public:
            virtual void advertising_started(error& err)=0;
            virtual void advertising_stopped()=0;
            virtual void service_added(service& srv, error& err)=0;
            virtual void central_connected(device& dev)=0;
            virtual void central_disconnected(device& dev)=0;
        };
    }
}

#endif // PERIPHERALPLUGINOBSERVER_H

