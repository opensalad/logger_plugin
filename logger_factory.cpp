#include "logger_factory.h"

#include "file_logger.h"
#include "stream_logger.h"
#include "invalid_logger.h"

#include <QFile>
#include <QVariant>
#include <QJsonDocument>
#include <QJsonObject>

ad::LoggerFactory::LoggerFactory()
    : __output_type(InvalidLoggerType)
{
    __loggers.push_back(new InvalidLogger());
}

void* ad::LoggerFactory::getInstance() const
{
    switch(__output_type)
    {
        case FileLoggerType: return getFileLogger();
        case StreamLoggerType: return getStreamLogger();
        default: return __loggers.first();
    }
    
    return __loggers.first();
}

void* ad::LoggerFactory::getFileLogger() const
{
    FileLogger *logger = new FileLogger();
    __loggers.push_back(logger);

    for(QString key : __properties.keys())
    {
        QString prop_value = __properties[key].toString();
        if(key == "file_path")
            logger->setFilePath(prop_value);
        else if(key == "log_level")
            logger->setLogLevel(FileLogger::logLevelFromString(prop_value));
        else if(key == "logger_id")
            logger->setId(prop_value);
        else if(key == "pattern")
            logger->setPattern(prop_value);
        else if(key == "pattern_params")
        {
            QMap<QString, QVariant> params = __properties[key].toMap();
            for(QString param : params.keys())
                logger->setPatternParam(param, params[param].toString());
        }
    }

    return (Logger<QString, QMap<QString, QString>>*)__loggers.back();
}

void* ad::LoggerFactory::getStreamLogger() const
{
    StreamLogger *logger = new StreamLogger();
    __loggers.push_back(logger);

    for(QString key : __properties.keys())
    {
        QString prop_value = __properties[key].toString();
        if(key == "log_level")
            logger->setLogLevel(FileLogger::logLevelFromString(prop_value));
        else if(key == "logger_id")
            logger->setId(prop_value);
        else if(key == "pattern")
            logger->setPattern(prop_value);
        else if(key == "pattern_params")
        {
            QMap<QString, QVariant> params = __properties[key].toMap();
            for(QString param : params.keys())
                logger->setPatternParam(param, params[param].toString());
        }
    }

    return (Logger<QString, QMap<QString, QString>>*)__loggers.back();
}

void ad::LoggerFactory::configure(bytebuf_t const &configuration)
{
    QJsonObject config = QJsonDocument::fromJson(configuration).object();
    QString logger_type_value = config.value("type").toString();
    __output_type = InvalidLoggerType;
    if(logger_type_value == "file_logger")
        __output_type = FileLoggerType;
    else if(logger_type_value == "stream_logger")
        __output_type = StreamLoggerType;

    for(QString key : config.keys())
    {
        __properties.insert(key, config.value(key));
    }
}

void ad::LoggerFactory::configureWithFile(bytebuf_t const &path_to_config_file)
{
    QFile config_file(path_to_config_file);
    config_file.open(QIODevice::ReadOnly);
    if(!config_file.isOpen())
        return;

    configure(config_file.readAll());
}

extern "C"
{
    ad::Factory<QByteArray>* getFactory()
    {
        static ad::LoggerFactory factory;
        return &factory;
    }
}