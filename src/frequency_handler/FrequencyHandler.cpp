#include "FrequencyHandler.h"


namespace unnamed::freq {

FrequencyHandler::FrequencyHandler(unsigned int targetFrequency_):
    targetFrequency { targetFrequency_ },
    measureIndex { 0 },
    delay { 1000 / targetFrequency } {
    measuredTime.resize(11);
}


void FrequencyHandler::StartTimer() {
    start = GetTime();
}

void FrequencyHandler::StopTimerAndAlign() {

    if (measureIndex >= measuredTime.size()) {
        std::make_heap(measuredTime.begin(), measuredTime.end());
        std::sort_heap(measuredTime.begin(), measuredTime.end());
        lastTime = measuredTime[5];
        unsigned int estimatedTime = targetFrequency * (lastTime + delay);
        if (estimatedTime > 1050) {
            if (delay > 30) {
                delay -= 5;
            }
        }
        else if (estimatedTime < 950) {
            delay += 5;
        }
        measureIndex = 0;
    }
    else {
        measuredTime[measureIndex++] = TimeDiff(start);
    }
}

unsigned int FrequencyHandler::GetFrequency() const {
    return 1000 / (delay + lastTime);
}

unsigned int FrequencyHandler::GetDelay() const {
    return delay;
}

unsigned int FrequencyHandler::GetLastTime() const {
    return lastTime;
}


}
