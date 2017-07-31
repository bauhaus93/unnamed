#pragma once

#include <iostream>
#include <fstream>

#include "Logger.h"

class FileLogger: public Logger {

	std::ofstream       file;

	void 				Log(const std::string& msg) override;

public:
                        FileLogger(LogLevel logLevel_, const std::string& filename);
						~FileLogger();
};
