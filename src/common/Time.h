#pragma once

#include <chrono>

namespace unnamed {


std::chrono::time_point<std::chrono::steady_clock> GetTime();
unsigned int TimeDiff(std::chrono::time_point<std::chrono::steady_clock> start);


}
