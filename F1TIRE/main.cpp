#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <clocale>
#include <cstdlib>
#include <limits>
#include "RaceMenu.h"
#include "TireMenu.h"
#include "TrackInfo.h"
#include "Simulation.h"
#include "SimulationFlow.h"


using namespace std;
using namespace F1Sim;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");

    vector<string> races = {
        "F1 Australian GP", "F1 Chinese GP", "F1 Japanese GP", "F1 Bahrain GP", "F1 Saudi Arabian GP", "F1 Miami GP",
        "F1 Emilia-Romagna GP", "F1 Monaco GP", "F1 Spain GP", "F1 Canada GP", "F1 Austria GP", "F1 Great Britain",
        "F1 Belgium GP", "F1 Hungary GP", "F1 Netherlands GP", "F1 Italy GP", "F1 Azerbaijan GP", "F1 Singapore GP",
        "F1 United States GP", "F1 Mexico GP", "F1 Brazil GP", "F1 Las Vegas GP", "F1 Qatar GP", "F1 Abu Dhabi GP",
    };

    showRaces(races);
    int selectedRace = getRaceSelection(races.size());
    string currentRace = races[selectedRace];

    clearScreen();
    cout << "Selected track: " << currentRace << "\n\n";

    Tire tire = chooseTire();
    clearScreen();

    int trackTemp;
    int totalLaps;

    if (argc >= 3) {
        totalLaps = atoi(argv[1]);
        trackTemp = atoi(argv[2]);

        if (totalLaps <= 0 || totalLaps > 150) {
            std::cout << "Invalid number of laps passed via command line. Using manual input\n";

            while (true) {
                std::cout << "Enter the total number of laps: ";
                std::cin >> totalLaps;

                if (std::cin.fail() || totalLaps <= 0 || totalLaps > 150) {
                    std::cin.clear(); 
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    std::cout << "Invalid input. Please enter a number between 1 and 150.\n";
                }
                else {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break; 
                }
            }
        }


        if (trackTemp < -20 || trackTemp > 100) {
            cout << "Invalid temperature passed via command line. Using automatic temp\n";
            trackTemp = F1Sim::getTrackTemperatureWithUserTemp(currentRace);
        }
    }
    else {
        trackTemp = F1Sim::getTrackTemperatureWithUserTemp(currentRace);
        cout << "Enter the total number of laps: ";
        cin >> totalLaps;
    }

    F1Sim::runSimulationLoop(tire, trackTemp, totalLaps);

    Tire best = suggestBestTireOption(trackTemp);
    cout << "\nBest long-term tire for current temp: " << best.type << "\n";

    return 0;
}