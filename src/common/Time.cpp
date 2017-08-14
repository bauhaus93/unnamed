#include "Time.h"

namespace unnamed {

static std::chrono::steady_clock clock {};


std::chrono::time_point<std::chrono::steady_clock> GetTime() {
    return clock.now();
}

unsigned int TimeDiff(std::chrono::time_point<std::chrono::steady_clock> start) {
	return static_cast<unsigned int>((std::chrono::nanoseconds(clock.now() - start).count())*1e-6);
}

}
