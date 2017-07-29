#include "Logger.h"


Logger::Logger(LogLevel logLevel_):
    logLevel { logLevel_ }{
}

void Logger::Debug(const char* msg) {
    if (logLevel <= LogLevel::DEBUG) {
        char *header = CreateLogHeader("DEBUG");
        Log(header, msg);
        delete[] header;
    }
}

void Logger::Info(const char* msg) {
    if (logLevel <= LogLevel::INFO) {
        char *header = CreateLogHeader("INFO");
        Log(header, msg);
        delete[] header;
    }
}

void Logger::Warning(const char* msg) {
    if (logLevel <= LogLevel::WARNING) {
        char *header = CreateLogHeader("WARNING");
        Log(header, msg);
        delete[] header;
    }
}

void Logger::Error(const char* msg) {
    if (logLevel <= LogLevel::ERROR) {
        char *header = CreateLogHeader("ERROR");
        Log(header, msg);
        delete[] header;
    }
}

char* Logger::CreateLogHeader(const char* level) {
    time_t rawTime;
    struct tm* localTime;
    char* str = new char[100];


    time(&rawTime);
    localTime = localtime(&rawTime);
    snprintf(str, 100, "[%04d-%02d-%02d %02d:%02d:%02d] %s - ", localTime->tm_year + 1900,
                                                                localTime->tm_mon,
                                                                localTime->tm_mday,
                                                                localTime->tm_hour,
                                                                localTime->tm_min,
                                                                localTime->tm_sec,
                                                                level);
    return str;
}

void Logger::Log(const char *header, const char* msg) {
    std::cerr << header << msg << std::endl;
}
