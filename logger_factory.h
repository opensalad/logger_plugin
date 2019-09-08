#pragma once

#include <factory.h>
#include <logger.h>

#include <QMap>
#include <QString>
#include <QVariant>
#include <QList>

namespace ad
{
    class LoggerFactory : public Factory<QByteArray>
    {
    public:
        LoggerFactory();

        enum LoggerType
        {
            FileLoggerType,
            StreamLoggerType,
            InvalidLoggerType
        };

		/**
		 * @brief Get instance for specified configuration.
		 * @param type specifies the instance general identifier
		 * @return opaque pointer to the requested instance
		 */
		void* getInstance() const override;

		/**
		 * @brief Configure the factory.
		 * 
		 * It is very usefull when trying to get some particlar type of instance from the bunch of available types.
		 * It parses the specified configuration string into usefull options and uses them in future actions.
		 * 
		 * @param configuration the configuration string
		 * @see configureWithFile
		 */
		void configure(bytebuf_t const &configuration) override;

		/**
		 * @brief Configure the factory using configuration file
		 * 
		 * This function is very likely to the function @a{configure()}, but it uses a path to the config file
		 * and reads all the configuration from that file.
		 * 
		 * @param path_to_config_file the path to the configuration file
		 * @see configure
		 */
		void configureWithFile(bytebuf_t const &path_to_config_file) override;

    private:
        void* getFileLogger() const;
        void* getStreamLogger() const;

    private:
        LoggerType __output_type;
        QMap<QString, QVariant> __properties;
        mutable QList<void*> __loggers;
    };
}