#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include "FileHandler.h"

namespace F1Sim {

    void saveSimulationResultCSV(
        const std::string& track,
        int temperature,
        int laps,
        const std::string& tireType,
        float tireWearPercent,
        float bestLapTimeSeconds,
        int recommendedPitLap,
        const std::vector<LapData>& lapHistory,
        const std::string& additionalInfo)
    {
        // Zapisz g³ówne podsumowanie symulacji
        std::ofstream summaryFile("simulation_summary.csv", std::ios::app);
        if (summaryFile.is_open()) {
            std::time_t t = std::time(nullptr);
            std::tm tm{};
#ifdef _WIN32
            localtime_s(&tm, &t);
#else
            localtime_r(&t, &tm);
#endif
            std::ostringstream dateStream;
            dateStream << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");

            summaryFile.seekp(0, std::ios::end);
            if (summaryFile.tellp() == 0) {
                summaryFile << "Date,Track,Temperature,Laps,TireType,TireWear%,BestLapTime(s),RecommendedPitLap,AdditionalInfo\n";
            }

            summaryFile << "\"" << dateStream.str() << "\","
                << "\"" << track << "\","
                << temperature << ","
                << laps << ","
                << "\"" << tireType << "\","
                << tireWearPercent << ","
                << bestLapTimeSeconds << ","
                << recommendedPitLap << ","
                << "\"" << additionalInfo << "\""
                << "\n";
            summaryFile.close();
        }

        // Zapisz szczegó³owe dane okr¹¿eñ
        std::ostringstream detailFileName;
        detailFileName << "lap_details_" << std::put_time(&tm, "%Y%m%d_%H%M%S") << ".csv";

        std::ofstream detailFile(detailFileName.str());
        if (detailFile.is_open()) {
            detailFile << "LapNumber,Degradation%,RemainingLife%,PitStop\n";

            for (const auto& lap : lapHistory) {
                detailFile << lap.lapNumber << ","
                    << lap.degradation << ","
                    << lap.remainingLife << ","
                    << (lap.pitStop ? "Yes" : "No") << "\n";
            }
            detailFile.close();
        }
    }
}
