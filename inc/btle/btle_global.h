#ifndef BTLE_GLOBAL_H
#define BTLE_GLOBAL_H

namespace btle {

    enum plugin_state
    {
        STATE_POWERED_ON,
        STATE_POWERED_OFF,
        STATE_POWERED_RESETTING,
        STATE_POWERED_UNKNOWN,
        STATE_POWERED_NON_SUPPORTED
    };
}

#ifdef _WIN32
#ifdef __GNUC__
#include <stdint-gcc.h>
#else
#include <stdint.h>
#endif
#else
#include <stdint.h>
#endif

#ifdef BTLE_EXPORT_IMPORT
#ifdef _MSC_VER
#ifdef BTLE_EXPORTS
#define BTLE_API __declspec(dllexport)
#else
#define BTLE_API __declspec(dllimport)
#endif
#elif __GNUC__
#ifdef BTLE_EXPORTS
#define BTLE_API __attribute__ ((visibility("default")))
#else
#define BTLE_API
#endif
#else
#define BTLE_API
#endif
#else
#define BTLE_API
#endif

#endif // BTLE_GLOBAL_H
