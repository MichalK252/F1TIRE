#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <clocale>
#include "RaceMenu.h"
#include "TireMenu.h"
#include "TrackInfo.h"
#include "Simulation.h"

using namespace std;
using namespace F1Sim;


void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


int main()
{
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
    cout << "\nSelected race: " << currentRace << "\n";

    clearScreen();
    cout << "Selected track: " << currentRace << "\n\n";

    Tire tire = chooseTire();
    clearScreen();
    cout << "Selected tire: " << tire << "\n";

    int temp = getTrackTemperatureWithUserTemp(currentRace);

    int totalLaps, currentLap;

    cout << "Enter the total number of laps: ";
    cin >> totalLaps;

    cout << "Enter the current lap: ";
    cin >> currentLap;

    clearScreen();
    calculateRemainingTireLife(tire, totalLaps, currentLap, temp);

    int pitLap = suggestPitLap(tire, temp, totalLaps, currentLap);
    int lapsLeft = totalLaps - pitLap;

    cout << "\n>>> Suggested PIT STOP on lap: " << pitLap << "\n";

    Tire nextTire = suggestNextTire(lapsLeft, temp);
    cout << ">>> Recommended tire after PIT STOP: " << nextTire.type
        << " (Degradation: " << nextTire.baseDegradation
        << "%, Optimal temp: " << nextTire.optimalTemp << "°C)\n";



    return 0;
}