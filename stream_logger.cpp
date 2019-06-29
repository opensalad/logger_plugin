#include "stream_logger.h"
#include <iostream>
#include <QDateTime>
#include <QThread>

namespace ad
{
	StreamLogger::StreamLogger()
		: __pattern("%t %d [%thd] [ %L ] %lid: %m")
	{}

	void StreamLogger::log(LogLevel level, char const *message) const
	{
		QString msg(message);
		format(level, msg);
		std::cout << msg.toStdString() << std::endl;
	}

	char const* StreamLogger::id() const { return __id.toStdString().c_str(); }
	char const* StreamLogger::pattern() const { return __pattern.toStdString().c_str(); }

	char const* StreamLogger::param(char const *param_key) const
	{
		if (__params.contains(param_key))
			return __params[param_key].toStdString().c_str();
		return nullptr;
	}

	char const** StreamLogger::paramList() const
	{
		char const **result = new char const*[__params.size() + 1];
		int i = 0;
		for (QString const &param : __params.keys()) { result[i++] = param.toStdString().c_str(); }
		result[i] = nullptr;
		return result;
	}

	char const* StreamLogger::uuid() const { return "stream_logger"; }
	void StreamLogger::setId(char const *id) { __id = QString(id); }
	void StreamLogger::setPattern(char const *pattern) { __pattern = QString(pattern); }
	void StreamLogger::setPatternParam(char const *param_key, char const *param_val) { __params[param_key] = QString(param_val); }

	void StreamLogger::format(LogLevel level, QString &msg) const
	{
		QString result = __pattern;
		result.replace("%d", (QDate::currentDate().toString("dd.MM.yyyy")));
		result.replace("%thd", QString("Thread %1").arg(reinterpret_cast<uint64_t>(QThread::currentThreadId()), 6));
		result.replace("%t", QTime::currentTime().toString("hh:mm:ss:zzz"));
		result.replace("%lid", __id);
		for (QString const &key : __params.keys())
			result.replace(QString("%%1").arg(key), __params[key]);
		QString lvl;
		switch (level)
		{
		case Trace: lvl = "TRACE";
			break;
		case Debug: lvl = "DEBUG";
			break;
		case Info: lvl = "INFO";
			break;
		case Warn: lvl = "WARN";
			break;
		case Error: lvl = "ERROR";
			break;
		default: lvl = "";
		}
		result.replace("%L", QString("%1").arg(lvl, 5));
		result.replace("%m", msg);
		msg = result;
	}
}
