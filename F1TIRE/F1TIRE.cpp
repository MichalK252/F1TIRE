#include <iostream>
#include <vector>
#include <string>
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
        cout << "Enter a race number: ";
        cin >> choice;
    } while (choice < 1 || choice > max);
    return choice - 1;
}


int main()
{
    vector<string> races = {
        "F1 Australian GP", "F1 Chinese GP", "F1 Japanese GP", "F1 Bahrain GP", "F1 Saudi Arabian GP", "F1 Miami GP",
        "F1 Emilia-Romagna GP", "F1 Monaco GP", "F1 Spain GP", "F1 Canada GP", "F1 Austria GP", "F1 Great Britain",
        "F1 Belgium GP", "F1 Hungary GP", "F1 Netherlands GP", "F1 Italy GP", "F1 Azerbaijan GP", "F1 Singapore GP",
        "F1 United-States GP", "F1 Mexico GP", "F1 Brazil GP", "F1 Las-Vegas GP", "F1 Qatar GP", "F1 Abu-Dhabi GP",
    };

    showRaces(races);
    int selectedRace = getRaceSelection(races.size());

    cout << "\nWybrano wyścig: " << races[selectedRace] << "\n";

    string currentRace = races[selectedRace];

    return 0;

}