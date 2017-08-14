#pragma once

#include <atomic>
#include <vector>
#include <algorithm>

#include "common/Time.h"
#include "logger/StdLogger.h"

namespace unnamed::freq {

class FrequencyHandler {

    std::chrono::time_point<std::chrono::steady_clock>  start;
    unsigned int                                        targetFrequency;
    unsigned int                                        measureIndex;
    std::vector<unsigned int>                           measuredTime;
    unsigned int                                        lastTime;
    std::atomic<unsigned int>                           delay;


public:
    explicit        FrequencyHandler(unsigned int targetFrequency_);
    void            StartTimer();
    void            StopTimerAndAlign();

    unsigned int    GetFrequency() const;
    unsigned int    GetDelay() const;
    unsigned int    GetLastTime() const;


};


}
