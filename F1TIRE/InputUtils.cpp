#include <iostream>
#include "InputUtils.h"

using namespace std;

void showHelp() {
    cout << "=== F1 Race Simulator Help ===\n\n";
    cout << "Options:\n";
    cout << "  --help           Show this help message\n";
    cout << "  --laps <number>  Set number of laps (1–100)\n";
    cout << "  --race <number>  Select race number from the list\n";
    cout << "\nIf no options are given, the simulator will ask for input interactively.\n";
}

int getLapsFromUser() {
    int laps;
    while (true) {
        cout << "Enter the total number of laps (1–100): ";
        if (cin >> laps && laps >= 1 && laps <= 100) {
            return laps;
        }
        cout << "Invalid input. Try again.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

int getRaceFromUser() {
    int race;
    while (true) {
        cout << "Enter race number (1–24): ";
        if (cin >> race && race >= 1 && race <= 24) {
            return race;
        }
        cout << "Invalid input. Try again.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}
