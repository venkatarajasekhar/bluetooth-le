#ifndef BTLE_GLOBAL_H
#define BTLE_GLOBAL_H

#include <stdint-gcc.h>

/** @def BTLE_API
 * Compiler specific symbol visibility attribute for public API symbols in BTLE.
 */
#ifdef BTLE_EXPORT_IMPORT
#ifdef _MSC_VER
#ifdef BTLE_EXPORTS
#define BTLE_API __declspec(dllexport)
#else /* !defined(BTLE_EXPORTS) */
#define BTLE_API __declspec(dllimport)
#endif /* !defined(BTLE_EXPORTS) */
#pragma warning(disable:4251) /* class 'X' needs to have dll-interface to be used by clients of class 'Y' */
#pragma warning(disable:4275) /* non dll-interface class 'X' used as base for dll-interface class 'Y' */
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
