#include "logger_plugin.h"

#include <QFile>
#include <QThread>
#include <QDateTime>

LoggerPlugin::LoggerPlugin()
	: __uuid(QUuid::createUuid()),
	__incremental(true),
	__level(Info),
	__format("[%t %d] [%thd] %L : %m\n"),
	__log_file(new QFile("./output.log"))
{
	__log_file->open(isIncremental() ? QIODevice::Append : QIODevice::WriteOnly);
	Core::instance()->registerPlugin(this);
}

bool LoggerPlugin::isIncremental() const
{
	return __incremental;
}

QString LoggerPlugin::formatMessage(LogLevel level, char const* message) const
{
	QString result = __format;
	result.replace("%d", QDate::currentDate().toString("dd.MM.yyyy"));
	result.replace("%thd", QString("Thread-%1").arg((uint64_t)QThread::currentThread()->currentThreadId()));
	result.replace("%t", QTime::currentTime().toString("hh:mm:ss:zzz"));
	QString lvl;
	switch (level)
	{
	case Trace: lvl = "TRACE"; break;
	case Debug: lvl = "DEBUG"; break;
	case Info: lvl = "INFO"; break;
	case Warn: lvl = "WARN"; break;
	case Error: lvl = "ERROR"; break;
	default: lvl = "";
	}
	result.replace("%L", lvl);
	result.replace("%m", QString(message));
	return result;
}

// Logger interface implementation
void LoggerPlugin::log(LogLevel level, char const* message) const
{
	if (__log_file == nullptr || !__log_file->isOpen())
		return;

	__log_file->write(formatMessage(level, message).toLatin1());
	__log_file->flush();
}

// Plugin interface implementation
QUuid LoggerPlugin::uuid() const
{
	return __uuid;
}