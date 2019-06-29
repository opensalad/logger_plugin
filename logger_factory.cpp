#include "logger_factory.h"

#include <QString>

#include "file_logger.h"
#include "stream_logger.h"
#include "invalid_logger.h"

namespace ad
{
	void* LoggerFactory::getInstance(char const *uuid, va_list &args) const
	{
		const std::string tmp(uuid);
		if (tmp == "file_logger")
		{
			char const *logfile = va_arg(args, char const*);
			return new FileLogger(QString(logfile));
		}

		if (tmp == "stream_logger")
			return new StreamLogger();

		return new InvalidLogger();
	}

}

EXTERN_C_GETTER(ad::LoggerFactory, ad::Logger, LOGGER)
