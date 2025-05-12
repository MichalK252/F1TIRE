#include <iostream>
#include <string>
#include <map>
#include "TrackInfo.h"

namespace F1Sim {
    int getTrackTemperatureWithUserTemp(const std::string& raceName) {
        static const std::map<std::string, int> raceTemperature = {
            {"F1 Australian GP", 26},
            {"F1 Chinese GP", 22},
            {"F1 Japanese GP", 19},
            {"F1 Bahrain GP", 34},
            {"F1 Saudi Arabian GP", 32},
            {"F1 Miami GP", 33},
            {"F1 Emilia-Romagna GP", 25},
            {"F1 Monaco GP", 30},
            {"F1 Spain GP", 31},
            {"F1 Canada GP", 24},
            {"F1 Austria GP", 23},
            {"F1 Great Britain", 20},
            {"F1 Belgium GP", 18},
            {"F1 Hungary GP", 29},
            {"F1 Netherlands GP", 21},
            {"F1 Italy GP", 28},
            {"F1 Azerbaijan GP", 35},
            {"F1 Singapore GP", 36},
            {"F1 United States GP", 30},
            {"F1 Mexico GP", 32},
            {"F1 Brazil GP", 29},
            {"F1 Las Vegas GP", 27},
            {"F1 Qatar GP", 37},
            {"F1 Abu Dhabi GP", 33}
        };

        int defaultTemp = 25;
        auto it = raceTemperature.find(raceName);
        if (it != raceTemperature.end()) {
            defaultTemp = it->second;
        }

        std::cout << "Track temperature: " << defaultTemp << "°C" << std::endl;
        std::cout << "Do you want to change the track temperature? (y/n): ";
        char answer;
        std::cin >> answer;

        if (answer == 'y' || answer == 'Y') {
            int userTemp;
            while (true) {
                std::cout << "Enter a new temperature (10°C - 60°C): ";
                std::cin >> userTemp;

                if (userTemp >= 10 && userTemp <= 60) {
                    return userTemp;
                }
                else {
                    std::cout << "Are you serious? Enter again." << std::endl;
                }
            }
        }
        return defaultTemp;
    }
}
 