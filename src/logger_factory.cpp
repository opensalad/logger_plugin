#include <logger_factory.h>
#include "file_logger.h"
#include <singleton.macro>

namespace ad
{
	SINGLETON(LoggerFactory)

	LoggerFactory::LoggerFactory() {}
	LoggerFactory::~LoggerFactory() {}

	LoggerFactory::logger_t& LoggerFactory::constructLogger()
	{
		logger_t *logger = new FileLogger();
		__loggers.insert(logger);
		return *logger;
	}

	void LoggerFactory::releaseLogger(QString const &logger_id)
	{
		for (logger_t *logger : __loggers)
		{
			if (logger->id() == logger_id)
			{
				__loggers.remove(logger);
				delete logger;
				return;
			}
		}
	}

	void LoggerFactory::setDefaultPattern(QString const &pattern)
	{
		__default_pattern = pattern;
	}

	LoggerFactory::logger_t& LoggerFactory::getLoggerFor(QString const &classname)
	{
		if (global().hasLoggerWithID(classname))
			return global().getLoggerWithID(classname);

		logger_t &logger = global().constructLogger();
		logger.setId(classname);
		if (global().__default_pattern != "")
			logger.setPattern(global().__default_pattern);

		logger.setLogLevel(global().__default_log_level);		
		return logger;
	}

	bool LoggerFactory::hasLoggerWithID(QString const &id)
	{
		for (logger_t *const &logger : __loggers)
		{
			if (logger->id() == id)
				return true;
		}
		return false;
	}

	LoggerFactory::logger_t& LoggerFactory::getLoggerWithID(QString const &id)
	{
		for (logger_t *const &logger : __loggers)
		{
			if (logger->id() == id)
				return *logger;
		}
		return *(logger_t*)nullptr;
	}

	void LoggerFactory::setPattern(QString const &pattern)
	{
		for (logger_t *logger : global().__loggers)
			logger->setPattern(pattern);
	}

	void LoggerFactory::setLogLevel(LogLevel level)
	{
		for (logger_t *logger : global().__loggers)
			logger->setLogLevel(level);

		global().__default_log_level = level;
	}
}