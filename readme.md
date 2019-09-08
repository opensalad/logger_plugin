# Logger

This is a simple logger implementation of [opensalad's](https://github.com/opensalad) [logger interface](https://github.com/opensalad/interfaces) based on [Qt](https://github.com/qt) library.

## Usage

```c++
#include <logger.h>
#include <factory.h>

#include <QString>
#include <QByteArray>
#include <QMap>
#include <QLibrary>

typedef ad::Factory<QByteArray> factory_t;
typedef ad::Logger<QString, QMap<QString, QString>> logger_t;
typedef factory_t* (*LoggerFactoryGetter)();

int main()
{
    LoggerFactoryGetter getFactory = (LoggerFactoryGetter)QLibrary::resolve("logger","getFactory");
    factory_t *factory = getFactory();
    factory->configureWithFile("logger.conf");
    logger_t *logger = (logger_t*)factory->getInstance();
    logger->log(ad::LogLevel::Info, "Hello world");
    return 0;
}
```

| Default configurations will be used if no configuration set.

## Config file properties

| Parameter | Description | Values |
|-|-|-|
| `"type"`      | The logger type | file_logger <br> stream_logger <br> [any other value]|
| `"log_level"` | The logging level | trace <br> debug <br> info <br> warn <br> error <br> all |
| `"logger_id"` | The identifier for the logger | any string |
| `"pattern"`   | The logging string format | any string with some placeholders |
| `"pattern_params"` | The parameters can be used in pattern | json object containing pairs of parameter key and parameter value (both must be strings) |

### Type specific properties

| Logger type | Parameter | Description | Values|
|-|-|-|-|
| *file_logger* | `"file_path"` | The path of the file where log messages will be outputed | \<path to log file> |

### Predefined parameters

| Parameter key | Value description 
|---------------|----------------------------
| `%thd`        | Current working thread id
| `%d`          | Date when printing the log (format is `"dd.MM.yyyy"`)
| `%t`          | Time when printing the log (format is `"hh:mm:ss:zzz"`)
| `%lid`        | Logger's ID
| `%m`          | Message to be printed
| `%L`          | Logging level

## Sample config file

```json
{
    "type" : "file_logger",
    "file_path" : "./my_log.log",
    "log_level" : "debug",
    "logger_id" : "hello_world_logger",
    "pattern" : "[%thd] [%d %t] : [%L] %m"
}
```