#pragma once
#include "logger_global.h"
#include "qt_logger.h"
#include <QUuid>
#include <QTextStream>

namespace ad
{
	class LOGGER_EXPORT FileLogger : public QtLogger
	{
	public:
		FileLogger();
		FileLogger(QString const &path);
		~FileLogger() override;
		void setPattern(QString const &format);
		void setLoggerUuid(QString const &uuid);
		QString formatMessage(LogLevel level, char const *message) const;

		//
		// Logger interface
		//
		void log(LogLevel level, char const *message) const override;
		void setId(char const *id) override;
		void setPattern(char const *pattern) override;
		void setPatternParam(char const *param_key, char const *param_val) override;
		char const* id() const override;
		char const* pattern() const override;
		char const* param(char const *param_key) const override;
		char const** paramList() const override;

		//
		// Plugin interface
		//
		char const* uuid() const override;
	private:
		QString __uuid;
		QString __logger_id;
		QMap<QString, QString> __param_tbl;
		QString __pattern;
		mutable QTextStream __log_file;
	};
}
