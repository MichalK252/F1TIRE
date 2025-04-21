#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "RaceMenu.h"
#include "TireMenu.h"
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

    return 0;
}