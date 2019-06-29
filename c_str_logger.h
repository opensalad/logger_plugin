#pragma once
#include "abstract_logger.h"

namespace ad
{
	class CStrLogger : public AbstractLogger
	{
	public:
		void trace(char const *message) const { log(Trace, message); }
		void debug(char const *message) const { log(Debug, message); }
		void info(char const *message) const { log(Info, message); }
		void warn(char const *message) const { log(Warn, message); }
		void error(char const *message) const { log(Error, message); }
	};
}
