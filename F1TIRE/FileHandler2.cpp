#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include "FileHandler2.h"

namespace F1Sim {

    static bool fileIsEmpty(const char* path) {
        std::ifstream f(path);
        return !(f.good() && f.peek() != std::ifstream::traits_type::eof());
    }

    void saveSimulationResultCSV(
        const std::string& track,
        int temperature,
        int laps,
        const std::string& tireType,
        float tireWearPercent,
        float bestLapTimeSeconds,
        int recommendedPitLap
    ) {
        bool writeHeader = fileIsEmpty("simulation_results.csv");

        std::ofstream file("simulation_results.csv", std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Could not open CSV file for writing.\n";
            return;
        }

        if (writeHeader) {
            file << "Date,Track,Temperature_C,Total_Laps,Tire_Type,"
                 << "Tire_Wear_Pct,Best_Lap_Time_s,Pit_Lap\n";
        }

        std::time_t now = std::time(nullptr);
        std::tm timeinfo;
        localtime_s(&timeinfo, &now);
        char dateBuf[20];
        std::strftime(dateBuf, sizeof(dateBuf), "%Y-%m-%d", &timeinfo);

        file << dateBuf          << ","
             << track            << ","
             << temperature      << ","
             << laps             << ","
             << tireType         << ","
             << std::fixed << std::setprecision(1) << tireWearPercent << ","
             << std::setprecision(3) << bestLapTimeSeconds            << ","
             << recommendedPitLap << "\n";

        file.close();
        std::cout << "Data saved to simulation_results.csv\n";
    }

}
