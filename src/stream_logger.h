#pragma once
#include "abstract_logger.h"

namespace ad
{
	class StreamLogger : public AbstractLogger
	{
	public:
		StreamLogger();
		void log(LogLevel level, string_t const &message) override;
		void setId(string_t const &id) override;
		void setPattern(string_t const &pattern) override;
		void setPatternParam(string_t const &param_key, string_t const &param_val) override;
		void enable() override;
		void disable() override;
		void setManager(PluginManager<string_t> *manager) override;
		string_t id() const override;
		string_t pattern() const override;
		string_t param(string_t const &param_key) const override;
		map_t paramList() const override;
		string_t uuid() const override;
		bool isEnabled() const override;
	protected:
		virtual void format(LogLevel level, QString &message) const;
	private:
		QString __id;
		QString __pattern;
		QMap<QString, QString> __params;
		bool __enabled;
	};
}
