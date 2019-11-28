#pragma once
#include <logger.h>
#include <QString>
#include <QMap>

namespace ad
{
	class InvalidLogger : public Logger<char const *, char const **>
	{
	public:
		void log(LogLevel, string_t const &) override {}
		void setId(string_t const &) override {}
		void setPattern(string_t const &) override {}
		void setPatternParam(string_t const &, string_t const &) override {}
		void enable() override {}
		void disable() override {}
		void setLogLevel(LogLevel level) override {}
		void setManager(PluginManager<string_t> *) override {}
		string_t id() const override { return ""; }
		string_t pattern() const override { return ""; }
		string_t param(string_t const &) const override { return ""; }
		map_t paramList() const override { return nullptr; }
		string_t uuid() const override { return "invalid_logger"; }
		bool isEnabled() const override { return true; }
		LogLevel logLevel() const override { return LogLevel::All; }
	};
}
