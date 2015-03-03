#ifndef BTLE_GLOBAL_H
#define BTLE_GLOBAL_H

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
#else /* !defined(BTLE_EXPORTS) */
#define BTLE_API __declspec(dllimport)
#endif /* !defined(BTLE_EXPORTS) */
#elif __GNUC__
#ifdef BTLE_EXPORTS
#define BTLE_API __attribute__ ((visibility("default")))
#else /* defined(BTLE_EXPORTS) */
#define BTLE_API
#endif /* defined(BTLE_EXPORTS) */
#else /* defined(__GNUC__) */
#error "Public symbol visibility attribute not defined for this compiler."
#define BTLE_API   // For Doxygen
#endif /* defined(_MSC_VER)*/
#else
#define BTLE_API
#endif

#endif // BTLE_GLOBAL_H
