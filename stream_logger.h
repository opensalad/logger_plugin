#pragma once
#include <logger.h>
#include <QMap>
class QString;

namespace ad
{
	class StreamLogger : public Logger
	{
	public:
		StreamLogger();
		void log(LogLevel level, char const *message) const override;
		void setId(char const *id) override;
		void setPattern(char const *pattern) override;
		void setPatternParam(char const *param_key, char const *param_val) override;
		char const* id() const override;
		char const* pattern() const override;
		char const* param(char const *param_key) const override;
		char const** paramList() const override;
		char const* uuid() const override;
	protected:
		virtual void format(LogLevel level, QString &message) const;
	private:
		QString __id;
		QString __pattern;
		QMap<QString, QString> __params;
	};
}
