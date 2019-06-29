#pragma once
#include "c_str_logger.h"
#if defined( _WIN32 ) || defined( _WIN64 ) || defined( WIN32 ) || defined( WIN64 )
#include <string>
#elif defined( __linux__ ) || defined( linux ) || defined( __linux )
#include <string.h>
#endif
namespace ad
{
	class StdLogger : public CStrLogger
	{
	public:
		void trace(std::string const &message) const { CStrLogger::trace(message.c_str()); }
		void debug(std::string const &message) const { CStrLogger::debug(message.c_str()); }
		void info(std::string const &message) const { CStrLogger::info(message.c_str()); }
		void warn(std::string const &message) const { CStrLogger::warn(message.c_str()); }
		void error(std::string const &message) const { CStrLogger::error(message.c_str()); }
	};
}
