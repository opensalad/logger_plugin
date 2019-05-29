#pragma once

#include "logger_plugin_global.h"
#include "qt_logger.h"
#include "../../core/include/core.h"

#include <QUuid>

class QFile;

class LOGGER_PLUGIN_EXPORT LoggerPlugin : public Plugin, public QtLogger
{
public:
	LoggerPlugin();
	LoggerPlugin(LoggerPlugin const& copy) = delete;
	LoggerPlugin(LoggerPlugin&& move) = delete;
	LoggerPlugin& operator =(LoggerPlugin const& assign) = delete;

	bool isIncremental() const;

	QString formatMessage(LogLevel level, char const* message) const;

	// Logger interface
	void log(LogLevel level, char const* message) const override;

	// Plugin interface
	QUuid uuid() const override;

private:
	QUuid __uuid;
	bool __incremental;
	LogLevel __level;
	QString __format;
	QFile* __log_file;
};
