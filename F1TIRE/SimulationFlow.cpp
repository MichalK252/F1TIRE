#include <iostream>
#include "Simulation.h"
#include "TireMenu.h"
#include "SimulationFlow.h"

using namespace std;

namespace F1Sim {

    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void runSimulationLoop(Tire& tire, int trackTemp, int totalLaps) {
        int currentLap = 1;
        bool continueRace = true;

        while (continueRace && currentLap < totalLaps) {
            clearScreen();
            calculateRemainingTireLife(tire, totalLaps, currentLap, trackTemp);

            int pitLap = suggestPitLap(tire, trackTemp, totalLaps, currentLap);
            if (pitLap == -1 || pitLap >= totalLaps) {
                cout << "\nTire should last until the end of the race.\n";
                break;
            }

            int lapsLeft = totalLaps - pitLap;
            Tire nextTire = suggestNextTire(lapsLeft, trackTemp);

            cout << "\n>>> Suggested PIT STOP on lap: " << pitLap << "\n\n";
            cout << ">>> Recommended tire after PIT STOP: " << nextTire.type
                << " (Degradation: " << nextTire.baseDegradation
                << "%, Optimal temp: " << nextTire.optimalTemp << "°C)\n";

            char choice;
            cout << "\nDo you want to continue simulation with this new tire? (y/n): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y') {
                tire = nextTire;
                currentLap = pitLap;
            }
            else {
                continueRace = false;
            }
        }

        cout << "\nRace simulation finished!\n";
    }
}
