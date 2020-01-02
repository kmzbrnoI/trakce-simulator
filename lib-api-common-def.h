#ifndef LIB_API_COMMON_DEF_H
#define LIB_API_COMMON_DEF_H

#include <QtGlobal>

#if defined(SIM_SHARED_LIBRARY)
#define SIM_SHARED_EXPORT Q_DECL_EXPORT
#else
#define SIM_SHARED_EXPORT Q_DECL_IMPORT
#endif

#ifdef Q_OS_WIN
#define CALL_CONV __stdcall
#else
#define CALL_CONV
#endif

#endif
