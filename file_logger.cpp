#include "file_logger.h"
#include <QFile>
#include <QThread>
#include <QDateTime>
#include <QTextStream>

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
		: __uuid("logger")
		, __pattern("%t %d [%thd] [ %L ] %lid: %m")
	{
		setFilePath(path);
	}

	void FileLogger::setFilePath(QString const &path)
	{
		if (path.endsWith(".log"))
			__log_file.setFileName(path);
		else
			__log_file.setFileName(path + ".log");
	}

	/**
	 * \brief The destructor.
	 * 
	 * Will close the opened file handler.
	 */
	FileLogger::~FileLogger() { __log_file.close(); }

	/**
	 * \brief Set the formatting pattern.
	 * \param format sets the formatting pattern
	 */
	void FileLogger::setPattern(QString const &format) { __pattern = format; }

	/**
	 * \brief Get the logger's ID
	 * \return the logger's ID
	 */
	FileLogger::string_t FileLogger::id() const { return __logger_id.toStdString().c_str(); }

	/**
	 * \brief Get the formatting pattern.
	 * \return the formatting pattern
	 */
	FileLogger::string_t FileLogger::pattern() const { return __pattern.toStdString().c_str(); }

	/**
	 * \brief Get the parameter for the specified key.
	 * \param param_key the required parameter's key
	 * \return the value for specified parameter key
	 */
	FileLogger::string_t FileLogger::param(string_t const &param_key) const
	{
		if (__param_tbl.contains(param_key))
			return __param_tbl[param_key].toStdString().c_str();
		return nullptr;
	}

	/**
	 * \brief Get the list of available parameters.
	 * \return null terminated C-style array containing the list ov valid parameter keys
	 */
	FileLogger::map_t FileLogger::paramList() const
	{
		return __param_tbl;
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
	QString FileLogger::formatMessage(LogLevel level, string_t msg) const
	{
		QString result = __pattern;
		result.replace("%d", (QDate::currentDate().toString("dd.MM.yyyy")));
		result.replace("%thd", QString("%1").arg((uint64_t) QThread::currentThreadId(), 6));
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
		result.replace("%m", msg);
		return result;
	}

	// Logger interface implementation

	/**
	 * \brief Print log to the output.
	 * \param level the logging level
	 * \param message the message to be printed
	 */
	void FileLogger::log(LogLevel level, string_t const &message)
	{
		while (!__log_file.isOpen())
			__log_file.open(QIODevice::Append | QIODevice::WriteOnly);
		if (level < logLevel())
			return;
		if (!__log_file.isOpen())
			return;

		QTextStream strm(&__log_file);
		strm << formatMessage(level, message).toLatin1() << '\n';
		strm.flush();
		strm.device()->close();
	}

	/**
	 * \brief Set the logger's ID.
	 * \param id the logger's ID
	 */
	void FileLogger::setId(string_t const &id) { __logger_id = QString(id); }

	/**
	 * \brief Set parameter.
	 * \param param_key the parameter's key
	 * \param param_val the parameter's value
	 */
	void FileLogger::setPatternParam(string_t const &param_key, string_t const &param_val) { __param_tbl[param_key] = QString(param_val); }

	// Plugin interface implementation

	/**
	 * \brief Get plugin specific uuid.
	 * \return plugin specific uuid
	 */
	FileLogger::string_t FileLogger::uuid() const { return __uuid; }
}