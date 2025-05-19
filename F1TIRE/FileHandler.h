#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>

namespace F1Sim {
    struct LapData {
        int lapNumber;
        double degradation;
        double remainingLife;
        bool pitStop;
    };

    void saveSimulationResultCSV(
        const std::string& track,
        int temperature,
        int laps,
        const std::string& tireType,
        float tireWearPercent,
        float bestLapTimeSeconds,
        int recommendedPitLap,
        const std::vector<LapData>& lapHistory,
        const std::string& additionalInfo = "");
}

#endif
