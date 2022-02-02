#include <string>
#include <cmath>
#include <cstdio>

#include "format.h"

#define HOUR_IN_SECONDS 3600
#define MIN_IN_SECONDS 60

std::string Format::ElapsedTime(long seconds) {
    // Convert seconds into -> HOURS:MIN:SECONDS format
    const int HOURS = std::floor(seconds / HOUR_IN_SECONDS);
    const int MINUTES = std::floor((seconds % HOUR_IN_SECONDS) / MIN_IN_SECONDS);
    const int SECONDS = seconds - HOURS * HOUR_IN_SECONDS - MINUTES * MIN_IN_SECONDS;
    
    std::string format = 
        std::to_string(HOURS) + ":" +
        std::to_string(MINUTES)+":" +
        std::to_string(SECONDS);

    return format;
}