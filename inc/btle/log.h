#ifndef LOG_H
#define LOG_H

#include <string>
#include "btle_global.h"

namespace btle {

    enum log_options{
        LOG_NONE        = 0,
        LOG_PRINT       = 0x01,
        LOG_FILE_STREAM = 0x02
    };

    // logger adapter
    typedef void (*kAdapter)(const std::string& str);

    class BTLE_API log{
    public:

        static log& instance();
        void set_options(int options);
        void install_adapter(kAdapter adapter);
        void trace(const char* tag,const char* method, const char* format, ...);


    private: // functions
        log();

    private: //data

        kAdapter adapter_;
        int      options_;
    };

    class logfunc
    {
        public:
            logfunc( const char* func_name);
             ~logfunc();
        private:
        const char* func_name_;
    };



    #define func_log \
    logfunc ___func(__FUNCTION__);\
    ___func;

    #ifdef _MSC_VER
    #define _log(...) log::instance().trace("LOG",__FUNCTION__,__VA_ARGS__);
    #define _log_warning(...) log::instance().trace("WARNING",__VA_ARGS__);
    #define _log_error(...) log::instance().trace("ERROR",__VA_ARGS__);
    #elif __GNUC__
    #define _log(...) log::instance().trace("LOG",__FUNCTION__,##__VA_ARGS__);
    #define _log_warning(...) log::instance().trace("WARNING",##__VA_ARGS__);
    #define _log_error(...) log::instance().trace("ERROR",##__VA_ARGS__);
    #endif
}

#endif // LOG_H

