#include <iostream>
#include <ctime>
#include <string>

enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3
};

class Logger {

    LogLevel        logLevel;

    virtual void    Log(const char* level, const char *msg);
    char*           CreateLogHeader(const char *level);

public:
     explicit       Logger(LogLevel logLevel_);

     void           Debug(const char* msg);
     void           Info(const char* msg);
     void           Warning(const char* msg);
     void           Error(const char* msg);
};
