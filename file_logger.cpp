#include "file_logger.h"
#include <QFile>
#include <QThread>
#include <QDateTime>

namespace ad
{
	/**
	 * \brief The default constructor.
	 * 
	 * The default log file will be generated at `./output.log`.
	 */
	FileLogger::FileLogger()
		: FileLogger("./output.log") {}

	/**
	 * \brief Constructs file logger with the given path.
	 * \param path the `.log` file path
	 */
	FileLogger::FileLogger(QString const &path)
		: __uuid("logger" + QUuid::createUuid().toString(QUuid::Id128))
		, __pattern("%t %d [%thd] [ %L ] %lid: %m")
	{
		if (path.endsWith(".log"))
			__log_file.setDevice(new QFile(path));
		else
			__log_file.setDevice(new QFile(path + ".log"));
	}

	/**
	 * \brief The destructor.
	 * 
	 * Will close the opened file handler.
	 */
	FileLogger::~FileLogger() { __log_file.device()->close(); }

	/**
	 * \brief Set the formatting pattern.
	 * \param format sets the formatting pattern
	 */
	void FileLogger::setPattern(QString const &format) { __pattern = format; }

	/**
	 * \brief Get the logger's ID
	 * \return the logger's ID
	 */
	char const* FileLogger::id() const { return __logger_id.toStdString().c_str(); }

	/**
	 * \brief Get the formatting pattern.
	 * \return the formatting pattern
	 */
	char const* FileLogger::pattern() const { return __pattern.toStdString().c_str(); }

	/**
	 * \brief Get the parameter for the specified key.
	 * \param param_key the required parameter's key
	 * \return the value for specified parameter key
	 */
	char const* FileLogger::param(char const *param_key) const
	{
		if (__param_tbl.contains(param_key))
			return __param_tbl[param_key].toStdString().c_str();
		return nullptr;
	}

	/**
	 * \brief Get the list of available parameters.
	 * \return null terminated C-style array containing the list ov valid parameter keys
	 */
	char const** FileLogger::paramList() const
	{
		char const **result = new char const* [__param_tbl.size() + 1];
		int i = 0;
		for (QString const &param : __param_tbl.keys()) { result[i++] = param.toStdString().c_str(); }
		result[i] = nullptr;
		return result;
	}

	/**
	 * \brief Set the logger uuid.
	 * \param uuid the uuid
	 */
	void FileLogger::setLoggerUuid(QString const &uuid) { __uuid = uuid; }

	/**
	 * \brief Format logger's pattern with corresponding parameters.
	 * \param level the logging level
	 * \param message the message to be printed
	 * \return formatted output
	 */
	QString FileLogger::formatMessage(LogLevel level, char const *message) const
	{
		QString result = __pattern;
		result.replace("%d", (QDate::currentDate().toString("dd.MM.yyyy")));
		result.replace("%thd", QString("Thread %1").arg((uint64_t) QThread::currentThreadId(), 6));
		result.replace("%t", QTime::currentTime().toString("hh:mm:ss:zzz"));
		result.replace("%lid", __logger_id);
		for (QString const &key : __param_tbl.keys())
			result.replace(QString("%%1").arg(key), __param_tbl[key]);
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
		QString msg(message);
		msg.replace('\n', "");
		msg.replace('\t', "");
		msg.replace(' ', "");
		result.replace("%m", msg);
		return result;
	}

	// Logger interface implementation

	/**
	 * \brief Print log to the output.
	 * \param level the logging level
	 * \param message the message to be printed
	 */
	void FileLogger::log(LogLevel level, char const *message) const
	{
		while (!__log_file.device()->isOpen())
			__log_file.device()->open(QIODevice::Append | QIODevice::WriteOnly);
		if (level < logLevel())
			return;
		if (__log_file.device() == nullptr || !__log_file.device()->isOpen())
			return;
		__log_file << formatMessage(level, message).toLatin1() << '\n';
		__log_file.flush();
		__log_file.device()->close();
	}

	/**
	 * \brief Set the logger's ID.
	 * \param id the logger's ID
	 */
	void FileLogger::setId(char const *id) { __logger_id = QString(id); }

	/**
	 * \brief Set the logger's formatting pattern.
	 * \param pattern the formatting pattern
	 */
	void FileLogger::setPattern(char const *pattern) { setPattern(QString(pattern)); }

	/**
	 * \brief Set parameter.
	 * \param param_key the parameter's key
	 * \param param_val the parameter's value
	 */
	void FileLogger::setPatternParam(char const *param_key, char const *param_val) { __param_tbl[param_key] = QString(param_val); }

	// Plugin interface implementation

	/**
	 * \brief Get plugin specific uuid.
	 * \return plugin specific uuid
	 */
	char const* FileLogger::uuid() const { return __uuid.toStdString().c_str(); }
}
