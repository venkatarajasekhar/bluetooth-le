#ifndef BTLE_GLOBAL_H
#define BTLE_GLOBAL_H

#include <QtCore/qglobal.h>

#ifndef uint8_t
#define uint8_t unsigned char
#endif


#if defined(BTLE_LIBRARY)
#  define BTLESHARED_EXPORT Q_DECL_EXPORT
#else
#  define BTLESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BTLE_GLOBAL_H
