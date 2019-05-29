#ifndef LOGGER_H
#define LOGGER_H

__interface Logger
{
	enum LogLevel
	{
		Trace,
		Debug,
		Info,
		Warn,
		Error
	};

	void log(LogLevel level, char const* message) const;
};

#endif
