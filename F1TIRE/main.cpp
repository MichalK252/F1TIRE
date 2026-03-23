#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <clocale>
#include <cstdlib>
#include <limits>
#include "RaceMenu.h"
#include "TireMenu.h"
#include "TrackInfo.h"
#include "Simulation.h"
#include "SimulationFlow.h"
#include "HelpDisplay.h"
#include "FileHandler2.h"

using namespace std;
using namespace F1Sim;

static const map<string, double> BASE_LAP_TIMES = {
    { "F1 Australian GP",     83.5  },
    { "F1 Chinese GP",        95.7  },
    { "F1 Japanese GP",       91.2  },
    { "F1 Bahrain GP",        91.5  },
    { "F1 Saudi Arabian GP",  87.5  },
    { "F1 Miami GP",          88.6  },
    { "F1 Emilia-Romagna GP", 76.7  },
    { "F1 Monaco GP",         73.8  },
    { "F1 Spain GP",          79.0  },
    { "F1 Canada GP",         74.4  },
    { "F1 Austria GP",        65.6  },
    { "F1 Great Britain",     85.4  },
    { "F1 Belgium GP",        105.9 },
    { "F1 Hungary GP",        77.2  },
    { "F1 Netherlands GP",    72.9  },
    { "F1 Italy GP",          81.0  },
    { "F1 Azerbaijan GP",     102.2 },
    { "F1 Singapore GP",      99.0  },
    { "F1 United States GP",  97.6  },
    { "F1 Mexico GP",         78.7  },
    { "F1 Brazil GP",         71.0  },
    { "F1 Las Vegas GP",      96.4  },
    { "F1 Qatar GP",          84.1  },
    { "F1 Abu Dhabi GP",      84.7  },
};

static void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");

    if (isHelpRequested(argc, argv)) {
        showHelp();
        return 0;
    }

    vector<string> races = {
        "F1 Australian GP",    "F1 Chinese GP",       "F1 Japanese GP",
        "F1 Bahrain GP",       "F1 Saudi Arabian GP", "F1 Miami GP",
        "F1 Emilia-Romagna GP","F1 Monaco GP",        "F1 Spain GP",
        "F1 Canada GP",        "F1 Austria GP",       "F1 Great Britain",
        "F1 Belgium GP",       "F1 Hungary GP",       "F1 Netherlands GP",
        "F1 Italy GP",         "F1 Azerbaijan GP",    "F1 Singapore GP",
        "F1 United States GP", "F1 Mexico GP",        "F1 Brazil GP",
        "F1 Las Vegas GP",     "F1 Qatar GP",         "F1 Abu Dhabi GP",
    };

    showRaces(races);
    int    selectedRace = getRaceSelection((int)races.size());
    string currentRace  = races[selectedRace];

    clearScreen();
    cout << "Selected track: " << currentRace << "\n\n";

    Tire tire = chooseTire();
    clearScreen();

    int trackTemp = 0;
    int totalLaps = 0;

    if (argc >= 3) {
        totalLaps = atoi(argv[1]);
        trackTemp = atoi(argv[2]);
        if (totalLaps <= 0 || totalLaps > 150) {
            cout << "Invalid laps from args. Enter manually.\n";
            totalLaps = 0;
        }
        if (trackTemp < -20 || trackTemp > 100) {
            cout << "Invalid temperature from args. Using suggested.\n";
            trackTemp = 0;
        }
    }

    if (trackTemp == 0)
        trackTemp = getTrackTemperatureWithUserTemp(currentRace);

    if (totalLaps <= 0) {
        while (true) {
            cout << "Enter the total number of laps (1-150): ";
            if (!(cin >> totalLaps) || totalLaps <= 0 || totalLaps > 150) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid. Enter a number between 1 and 150.\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }
    }

    double baseLapTime = 90.0;
    auto it = BASE_LAP_TIMES.find(currentRace);
    if (it != BASE_LAP_TIMES.end())
        baseLapTime = it->second;

    SimulationResult result = runSimulationLoop(tire, trackTemp, totalLaps, baseLapTime);

    cout << "\n";
    Tire best = suggestBestTireOption(trackTemp);
    cout << "\nRecommended tire for temp " << trackTemp << " C: "
         << best.type << "\n";

    char saveChoice = 'n';
    cout << "\nSave data to CSV? (y/n): ";
    if (cin >> saveChoice) cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (saveChoice == 'y' || saveChoice == 'Y') {
        int pitLap = (result.actualPitLap > 0)      ? result.actualPitLap
                   : (result.recommendedPitLap > 0) ? result.recommendedPitLap : 0;

        saveSimulationResultCSV(
            currentRace,
            trackTemp,
            totalLaps,
            result.finalTireType,
            (float)result.finalTireWear,
            (float)result.bestLapTime,
            pitLap
        );
    } else {
        cout << "Data not saved.\n";
    }

    return 0;
}
