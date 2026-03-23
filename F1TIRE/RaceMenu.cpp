#include "RaceMenu.h";
#include <iostream>;
#include <iomanip>

using namespace std;

namespace F1Sim {
    void showRaces(const vector<std::string>& races)
    {
        cout << R"(
 ________  _____          _________  ___  ________  _______      
|\  _____\/ __  \        |\___   ___\\  \|\   __  \|\  ___ \     
\ \  \__/|\/_|\  \       \|___ \  \_\ \  \ \  \|\  \ \   __/|    
 \ \   __\|/ \ \  \           \ \  \ \ \  \ \   _  _\ \  \_|/__  
  \ \  \_|    \ \  \           \ \  \ \ \  \ \  \\  \\ \  \_|\ \ 
   \ \__\      \ \__\           \ \__\ \ \__\ \__\\ _\\ \_______\
    \|__|       \|__|            \|__|  \|__|\|__|\|__|\|_______|
)" << endl;

        for (size_t i = 0; i < races.size(); ++i) {
            cout << setw(2) << i + 1 << ". " << races[i] << "\n";
        }
    }

    int getRaceSelection(int max) {
        int choice;
        do {
            cout << "\nEnter a race number: ";
            if (!(cin >> choice)) {
                cout << "Invalid input. Please enter a number between 1 and " << max << ".\n";
                cin.clear(); 
                cin.ignore(10000, '\n');
                continue; 
            }

            if (choice < 1 || choice > max) {
                cout << "Please enter a number between 1 and " << max << ".\n";
            }

        } while (choice < 1 || choice > max);

        return choice - 1;
    }

}