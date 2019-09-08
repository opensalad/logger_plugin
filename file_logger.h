#pragma once
#include "logger_global.h"
#include "qt_logger.h"
#include <QUuid>
#include <QFile>

namespace ad
{
	class LOGGER_EXPORT FileLogger : public QtLogger
	{
	public:
		FileLogger();
		FileLogger(QString const &path);
		~FileLogger() override;
		void setLoggerUuid(QString const &uuid);
		QString formatMessage(LogLevel level, string_t message) const;
		void setFilePath(QString const &path);

		//
		// Logger interface
		//
		void enable() override {}
		void disable() override {}
		bool isEnabled() const override { return true; }

		void log(LogLevel level, string_t const &message) override;
		void setId(string_t const &id) override;
		void setPattern(string_t const &pattern) override;
		void setPatternParam(string_t const &param_key, string_t const &param_val) override;
		string_t id() const override;
		string_t pattern() const override;
		string_t param(string_t const &param_key) const override;
		map_t paramList() const override;

		//
		// Plugin interface
		//
		string_t uuid() const override;
		void setManager(PluginManager<string_t> *) override {}
	private:
		QString __uuid;
		QString __logger_id;
		QMap<QString, QString> __param_tbl;
		QString __pattern;
		QFile __log_file;
	};
}
