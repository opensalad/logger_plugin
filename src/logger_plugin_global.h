#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LOGGER_PLUGIN_LIB)
#  define LOGGER_PLUGIN_EXPORT Q_DECL_EXPORT
# else
#  define LOGGER_PLUGIN_EXPORT Q_DECL_IMPORT
# endif
#else
# define LOGGER_PLUGIN_EXPORT
#endif
