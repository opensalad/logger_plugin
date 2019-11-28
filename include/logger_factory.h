#pragma once

#include <factory.h>
#include <logger.h>

#include <QSet>

template <typename k, typename v>
class QMap;
class QString;

#define LOGGER(classname) \
static ad::LoggerFactory::logger_t& logger = ad::LoggerFactory::getLoggerFor(#classname)

namespace ad
{
	class LoggerFactory
	{
		LoggerFactory();
		~LoggerFactory();

	public:
		typedef ad::Logger<QString, QMap<QString, QString>> logger_t;

	public:
		logger_t& constructLogger();
		void releaseLogger(QString const &logger_id);
		void setDefaultPattern(QString const &pattern);
		bool hasLoggerWithID(QString const &id);
		logger_t& getLoggerWithID(QString const &id);

	public:
		static LoggerFactory &global();
		static logger_t& getLoggerFor(QString const &classname);
		static void setPattern(QString const &pattern);
		static void setLogLevel(LogLevel level);

	private:
		QString __default_pattern;
		LogLevel __default_log_level;
		QSet<logger_t*> __loggers;
	};
}