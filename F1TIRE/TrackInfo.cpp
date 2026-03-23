#include "TrackInfo.h"
#include <iostream>
#include <map>
#include <string>
#include <limits>

using namespace std;

namespace F1Sim {

    static const map<string, int> TRACK_TEMPERATURES = {
        { "F1 Australian GP",    35 },
        { "F1 Chinese GP",       28 },
        { "F1 Japanese GP",      22 },
        { "F1 Bahrain GP",       42 },
        { "F1 Saudi Arabian GP", 40 },
        { "F1 Miami GP",         45 },
        { "F1 Emilia-Romagna GP",27 },
        { "F1 Monaco GP",        30 },
        { "F1 Spain GP",         38 },
        { "F1 Canada GP",        25 },
        { "F1 Austria GP",       26 },
        { "F1 Great Britain",    24 },
        { "F1 Belgium GP",       20 },
        { "F1 Hungary GP",       50 },
        { "F1 Netherlands GP",   23 },
        { "F1 Italy GP",         38 },
        { "F1 Azerbaijan GP",    35 },
        { "F1 Singapore GP",     55 },
        { "F1 United States GP", 40 },
        { "F1 Mexico GP",        30 },
        { "F1 Brazil GP",        48 },
        { "F1 Las Vegas GP",     18 },
        { "F1 Qatar GP",         52 },
        { "F1 Abu Dhabi GP",     38 },
    };

    int getTrackTemperatureWithUserTemp(const string& raceName) {
        int suggestedTemp = 30;

        auto it = TRACK_TEMPERATURES.find(raceName);
        if (it != TRACK_TEMPERATURES.end()) {
            suggestedTemp = it->second;
        }

        cout << "Suggested track surface temp for " << raceName
             << ": " << suggestedTemp << " C\n";
        cout << "Enter track temperature (or press Enter to use "
             << suggestedTemp << " C): ";

        string line;
        if (cin.peek() == '\n') cin.ignore();
        getline(cin, line);

        if (line.empty()) {
            cout << "Using: " << suggestedTemp << " C\n";
            return suggestedTemp;
        }

        try {
            int userTemp = stoi(line);
            if (userTemp < -20 || userTemp > 100) {
                cout << "Out of range. Using suggested: " << suggestedTemp << " C\n";
                return suggestedTemp;
            }
            cout << "Using: " << userTemp << " C\n";
            return userTemp;
        } catch (...) {
            cout << "Invalid. Using suggested: " << suggestedTemp << " C\n";
            return suggestedTemp;
        }
    }

}
