#include "StdLogger.h"

namespace unnamed::logging {

const std::unique_ptr<Logger> stdLogger = std::make_unique<Logger>(LogLevel::LOG_LEVEL);

}
