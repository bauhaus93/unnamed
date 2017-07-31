#pragma once

#include <memory>

#include "Logger.h"

extern const std::unique_ptr<Logger> stdLogger;

#define LOG_LEVEL INFO

#if LOG_LEVEL == DEBUG
    #define DEBUG(msg) stdLogger->Debug(msg)
    #define INFO(msg) stdLogger->Info(msg)
    #define WARN(msg) stdLogger->Warn(msg)
    #define ERROR(msg) stdLogger->Error(msg)
#elif LOG_LEVEL == INFO
    #define DEBUG(msg)
    #define INFO(msg) stdLogger->Info(msg)
    #define WARN(msg) stdLogger->Warn(msg)
    #define ERROR(msg) stdLogger->Error(msg)
#elif LOG_LEVEL == WARN
    #define DEBUG(msg)
    #define INFO(msg)
    #define WARN(msg) stdLogger->Warn(msg)
    #define ERROR(msg) stdLogger->Error(msg)
#elif LOG_LEVEL == ERROR
    #define DEBUG(msg)
    #define INFO(msg)
    #define WARN(msg)
    #define ERROR(msg) stdLogger->Error(msg)
#endif
