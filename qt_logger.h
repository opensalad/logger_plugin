#pragma once
#include "std_logger.h"
#include <QString>

namespace ad
{
	class QtLogger : public StdLogger
	{
	public:
		void trace(QString const &message) const { StdLogger::trace(message.toStdString()); }
		void debug(QString const &message) const { StdLogger::debug(message.toStdString()); }
		void info(QString const &message) const { StdLogger::info(message.toStdString()); }
		void warn(QString const &message) const { StdLogger::warn(message.toStdString()); }
		void error(QString const &message) const { StdLogger::error(message.toStdString()); }
	};
}
