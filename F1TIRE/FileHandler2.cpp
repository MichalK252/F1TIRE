#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include "FileHandler2.h"


namespace F1Sim {

    void saveSimulationResultCSV(
        const std::string& track,
        int temperature,
        int laps,
        const std::string& tireType,
        float tireWearPercent,
        float bestLapTimeSeconds,
        int recommendedPitLap
    ) {
        std::ofstream file("simulation_results.csv", std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Could not open CSV file for writing.\n";
            return;
        }

        std::time_t now = std::time(nullptr);
        std::tm timeinfo;
        localtime_s(&timeinfo, &now);

        char dateBuffer[20];
        std::strftime(dateBuffer, sizeof(dateBuffer), "%Y-%m-%d", &timeinfo);

        file << "Track: " << track << ","
            << "Temperature: " << temperature << ","
            << "Laps: " << laps << ","
            << "Tire type: " << tireType << ","
            << "Tire wear percent: " << std::fixed << std::setprecision(2) << tireWearPercent << ","
            << "Best lap time seconds: " << bestLapTimeSeconds << ","
            << "Recommended pit lap: " << recommendedPitLap << ","
            << "Date: " << dateBuffer << ";" << "\n";

        file.close();
    }

}
