#pragma once
#include "abstract_logger.h"

namespace ad
{
	class QtLogger : public AbstractLogger
	{
	public:
		void trace(string_t const& message) { log(LogLevel::Trace, message); }
		void debug(string_t const& message) { log(LogLevel::Debug, message); }
		void info(string_t const& message) { log(LogLevel::Info, message); }
		void warn(string_t const& message) { log(LogLevel::Warn, message); }
		void error(string_t const& message) { log(LogLevel::Error, message); }
	};
}
