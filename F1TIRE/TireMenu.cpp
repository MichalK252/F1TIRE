#include "TireMenu.h"
#include <iostream>
using namespace std;

namespace F1Sim {

    void showTireOptions() {
        cout << R"(
   _____ _    _  ____   ____   _____ ______   _______ _____ _____  ______
  / ____| |  | |/ __ \ / __ \ / ____|  ____| |__   __|_   _|  __ \|  ____|
 | |    | |__| | |  | | |  | | (___ | |__       | |    | | | |__) | |__
 | |    |  __  | |  | | |  | |\___ \|  __|      | |    | | |  _  /|  __|
 | |____| |  | | |__| | |__| |____) | |____     | |   _| |_| | \ \| |____
  \_____|_|  |_|\____/ \____/|_____/|______|    |_|  |_____|_|  \_\______|

)" << endl;

        cout << "  Tire    | Dur/lap | Opt track temp | Expected laps\n";
        cout << "  --------|---------|----------------|---------------\n";
        cout << "  1. Soft         |  4.0%  |    ~45 C hot   |  ~20-25 laps\n";
        cout << "  2. Medium       |  2.8%  |    ~38 C       |  ~28-35 laps\n";
        cout << "  3. Hard         |  2.0%  |    ~30 C cool  |  ~40-50 laps\n";
        cout << "  4. Intermediate |  2.5%  |    ~20 C damp  |  ~25-35 laps\n";
        cout << "  5. Wet          |  2.2%  |    ~10 C wet   |  ~20-30 laps\n";
    }

    Tire chooseTire() {
        int choice = 0;
        showTireOptions();

        do {
            cout << "\nYour choice (1-5): ";
            if (!(cin >> choice)) {
                cout << "Invalid input. Enter a number between 1 and 5.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                choice = 0;
                continue;
            }
            if (choice < 1 || choice > 5)
                cout << "Please choose between 1 and 5.\n";
        } while (choice < 1 || choice > 5);

        Tire selected;
        switch (choice) {
        case 1: selected = { "Soft",         4.0, 45 }; break;
        case 2: selected = { "Medium",       2.8, 38 }; break;
        case 3: selected = { "Hard",         2.0, 30 }; break;
        case 4: selected = { "Intermediate", 2.5, 20 }; break;
        case 5: selected = { "Wet",          2.2, 10 }; break;
        }

        cout << "\nSelected: " << selected.type << "\n";
        return selected;
    }

}
