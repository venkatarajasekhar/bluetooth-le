#ifndef PLUGIN_START_FAILED_H
#define PLUGIN_START_FAILED_H

#include <stdexcept>
#include <string>
#include "btle_global.h"

namespace btle {
    namespace exceptions {
        class BTLE_API plugin_start_failed: public std::runtime_error{
        public:
            explicit plugin_start_failed(const std::string& what, int err);
            plugin_start_failed();
            plugin_start_failed(const plugin_start_failed& other);
        private:
            int error_;
        };
    }
}

#endif // FAILED_TO_START_PLUGIN_H

