#ifndef PERIPHERALPLUGINOBSERVER_H
#define PERIPHERALPLUGINOBSERVER_H

namespace btle {
    class error;
    class service;
    class device;
    class characteristic;
    class descriptor;
    class attributerequest;
    namespace peripheral {
        class peripheralpluginobserver{
        public:
            virtual void advertising_started(error& err)=0;
            virtual void advertising_stopped()=0;
            virtual void service_added(service& srv, error& err)=0;
            virtual void central_connected(device& central)=0;
            virtual void central_disconnected(device& central)=0;
            virtual void descriptor_written(device& central, service& srv, characteristic& chr, descriptor& desc);
            virtual attributerequest characteristic_read(device& central, service& srv, characteristic& chr)=0;
            virtual void characteristic_write(device& central,service& srv,characteristic& chr,std::string& data)=0;
            virtual void notify_channel_free(device& central)=0;
        };
    }
}

#endif // PERIPHERALPLUGINOBSERVER_H

