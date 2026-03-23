#pragma once
#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include "TireMenu.h"

namespace F1Sim {

    struct SimulationResult {
        double      finalTireWear;
        double      bestLapTime;
        int         recommendedPitLap;
        int         actualPitLap;
        std::string finalTireType;
    };

    double computeLapDegradation(const Tire& tire, int trackTemp, double currentWear);
    double computeLapTime(const Tire& tire, double tireWear, double baseLapTime);

    void printLapStatus(int currentLap, int totalLaps, double totalDegradation,
                        double remainingLife, double lapTime);

    void printForecast(const Tire& tire, int currentLap, int totalLaps,
                       int trackTemp, double totalDegradation);

    int  suggestPitLap(const Tire& tire, int trackTemp, int totalLaps,
                       int currentLap, double currentWear);

    Tire suggestNextTire(int lapsRemaining, int trackTemp);
    Tire suggestBestTireOption(int trackTemp);
}

#endif
