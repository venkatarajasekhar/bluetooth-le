#ifndef PERIPHERALPLUGINOBSERVER_H
#define PERIPHERALPLUGINOBSERVER_H

namespace btle {
    class error;
    class service;
    class device;
    class characteristic;
    class descriptor;
    namespace peripheral {
        class peripheralpluginobserver{
        public:
            virtual void advertising_started(error& err)=0;
            virtual void advertising_stopped()=0;
            virtual void service_added(service& srv, error& err)=0;
            virtual void central_connected(device& central)=0;
            virtual void central_disconnected(device& central)=0;
            virtual void descriptor_written(device& central, service& srv, characteristic& chr, descriptor& desc);
        };
    }
}

#endif // PERIPHERALPLUGINOBSERVER_H

