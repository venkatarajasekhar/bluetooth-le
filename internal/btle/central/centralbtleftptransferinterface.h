#ifndef CENTRALBTLEFTPTRANSFERINTERFACE_H
#define CENTRALBTLEFTPTRANSFERINTERFACE_H

#include <string>

namespace btle {
    class device;
    namespace central {

        /**
         * @brief The centralbtleftptransferinterface class, interface for handling library ftp
         * protocol packet transfer
         */
        class centralbtleftptransferinterface{
        public:

            /**
             * @brief write_btle_ftp, note this function is called from different context!p
             * @param dev
             * @param buffer
             */
            virtual void write_btle_ftp(device& dev, const std::string& buffer)=0;

            /**
             * @brief read_btle_ftp, note this function is called from different context!
             * @param dev
             * @param buffer
             */
            virtual int read_btle_ftp(device& dev, std::string& buffer, bool ack)=0;

        };
    }
}

#endif // CENTRALBTLEFTPTRANSFERINTERFACE_H

