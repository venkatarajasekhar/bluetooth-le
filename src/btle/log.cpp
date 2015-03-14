
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <sstream>

#include "btle/log.h"

using namespace btle;

namespace {
    #ifdef _MSC_VER
    #define __vsnprintf(buf, fmt, ap) _vsnprintf(const_cast<char*>(buf.data()), buf.size(), fmt, ap)
    #else
    #define __vsnprintf(buf, fmt, ap) ::vsnprintf(const_cast<char*>(buf.data()), buf.size(), fmt, ap)
    #endif

    #define LOG_BUFFER_SIZE 1000

    static void default_adapter( const std::string& str )
    {
        std::printf("%s\n",str.c_str());
    }
}

log& log::instance()
{
    static log instance;
    return instance;
}

void log::set_options(int options)
{
    options_ |= options;
}

void log::trace(const char* tag,const char* method, const char* format, ...)
{
    std::va_list ap;
    std::stringstream ss;
    std::string buf(LOG_BUFFER_SIZE, 0);
    va_start(ap, format);
    __vsnprintf(buf, format, ap);
    va_end(ap);
    ss << '[' << tag << ']' << '[' << method << "] " << buf;
    (*instance().adapter_)(ss.str());
}

log::log()
: adapter_(&::default_adapter),
  options_(0)
{
}

// logfunc class
logfunc::logfunc( const char* func_name)
: func_name_(func_name)
{
    log::instance().trace("FUNC",func_name_,"[-->]");
}

logfunc::~logfunc()
{
    log::instance().trace("FUNC",func_name_,"[<--]");
}
