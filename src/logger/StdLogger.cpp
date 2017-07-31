#include "StdLogger.h"

const std::unique_ptr<Logger> stdLogger = std::make_unique<Logger>(LogLevel::LOG_LEVEL);
