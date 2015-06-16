#ifndef PERIPHERAL_H
#define PERIPHERAL_H

#include "btle/base.h"
#include "btle/uuid.h"
#include "btle/device.h"
#include "btle/bda.h"
#include "btle/attributerequest.h"
#include "btle/gatt_services/btlelibservice.h"
#include "btle/peripheral/peripheralplugininterface.h"
#include "btle/peripheral/peripheralpluginobserver.h"

namespace btle {
    namespace peripheral {
        /**
         * @brief The peripheral class, library main peripheral interface
         */
        class peripheral: private peripheralpluginobserver, public base{
        public:

            peripheral();

        public: // plugin start/stop etc...

            const std::vector<std::string>& plugins_available() const;
            void start(const std::string& plugin_name);
            void auto_start();
            void stop();

        public: //

            peripheral& operator << (const service& srv);
            void advertise_btle_lib_service();

        public: // ftp api
            
            void write_file(device& central, std::ostream& stream, int identifier=0);

        private: // from observer

            void plugin_state_changed(plugin_state state);
            void advertising_started(error& err);
            void advertising_stopped();
            void service_added(service& srv, error& err);
            void central_connected(device& dev);
            void central_disconnected(device& dev);
            void descriptor_written(device& central, service& srv, characteristic& chr, descriptor& desc);
            btle::attributerequest characteristic_read(device& central, service& srv, characteristic& chr);
            void characteristic_write(device& central,service& srv,characteristic& chr,std::string& data);
            void notify_channel_free(device& central);

        public: // callbacks
            
            virtual void btle_ftp_in_progress(device& dev, double progress, const std::string& data, int identifier);
            virtual void btle_ftp_out_progress(device& dev, double progress, int identifier);
            
        private:
            peripheralplugininterface* plugin_;
            std::vector<peripheralplugininterface*> plugins_;
            unsigned int flags_;
            std::vector<std::string> plugins_available_;
            gattdatabase db_;
            gatt_services::btlelibservice btlelib_service_;
        };
    }
}

#endif // PERIPHERAL_H

