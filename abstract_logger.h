#pragma once
#include <logger.h>
#include <QMap>
#include <QString>

namespace ad
{
	class AbstractLogger : public Logger<QString, QMap<QString, QString>>
	{
	public:
		enum LoggerFlag
		{
			Append = 0x00000001,
			CleanOnStart = 0x00000002,
			SplitToFiles = 0x00000003
		};

	public:
		AbstractLogger()
			: __level(Info)
			, __flags(CleanOnStart) {}

		LogLevel logLevel() const { return __level; }
		void setLogLevel(LogLevel const level) { __level = level; }

		void setFlag(LoggerFlag const flag, bool const set = true)
		{
			if (!set)
				__flags &= ~flag;
			else
				__flags |= flag;
		}

		void setFlags(int const flags) { __flags = flags; }
		bool getFlag(LoggerFlag const flag) const { return getFlags() & flag; }
		int getFlags() const { return __flags; }
	private:
		LogLevel __level;
		int __flags;
	};
}
