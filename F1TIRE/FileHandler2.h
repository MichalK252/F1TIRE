#pragma once

#include <string>

namespace F1Sim {
    void saveSimulationResultCSV(
        const std::string& track,
        int temperature,
        int laps,
        const std::string& tireType,
        float tireWearPercent,
        float bestLapTimeSeconds,
        int recommendedPitLap
    );
}
