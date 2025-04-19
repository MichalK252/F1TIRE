#include "RaceMenu.h";
#include<iostream>;
#include <iomanip>

using namespace std;

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
        cin >> choice;
    } while (choice < 1 || choice > max);
    return choice - 1;
}