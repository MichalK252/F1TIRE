#include <iostream>
#include <iomanip>
#include "Simulation.h"

using namespace std;

namespace F1Sim {
    const double TEMP_THRESHOLD = 5.0;  
    const double CRITICAL_LIFE_THRESHOLD = 10.0;  

    double computeLapDegradation(const Tire& tire, int trackTemp) {
        double lapDegradation = tire.baseDegradation;

        if (trackTemp < tire.optimalTemp - TEMP_THRESHOLD ||
            trackTemp > tire.optimalTemp + TEMP_THRESHOLD) {
            lapDegradation *= 1.5;
        }

        return lapDegradation;
    }

    void printLapStatus(int currentLap, int totalLaps, double totalDegradation, double remainingLife) {
        cout << "Lap: " << currentLap << " / " << totalLaps
            << " | Degradation: " << totalDegradation << "%"
            << " | Remaining life: " << remainingLife << "%\n";
    }

    void printForecast(const Tire& tire, int currentLap, int totalLaps, int trackTemp, double totalDegradation) {
        double forecastDegradation = totalDegradation;
        int pitStopLap = -1;

        cout << "\n Degradation forecast:\n";

        for (int i = currentLap + 1; i <= totalLaps; i++) {
            double lapDegradation = computeLapDegradation(tire, trackTemp);
            forecastDegradation += lapDegradation;
            double forecastRemaining = 100.0 - forecastDegradation;

            if (forecastRemaining < 0.0) forecastRemaining = 0.0;

            cout << "Lap " << i << ": Remaining " << forecastRemaining << "%";

            if (forecastDegradation >= 100.0 && pitStopLap < 0) {
                pitStopLap = i;
            }
            cout << "\n";

            if (pitStopLap > 0 && i >= pitStopLap) {
                break;
            }
        }
    }

    void calculateRemainingTireLife(Tire& tire, int totalLaps, int currentLap, int trackTemp) {
        if (totalLaps <= 0 || currentLap < 0 || currentLap > totalLaps) {
            cout << "Invalid number of laps\n";
            return;
        }

        if (tire.baseDegradation <= 0.0 || tire.baseDegradation > 20.0) {
            cout << "Invalid tire degradation value\n";
            return;
        }

        double totalDegradation = 0.0;
        double remainingLife = 100.0;
        int pitStopLap = -1;

        cout << fixed << setprecision(2);
        cout << "\n Tire wear simulation: " << tire.type
            << " (optimal temp: " << tire.optimalTemp << "°C)\n";
        cout << "------------------------------------------------\n";

        for (int i = 1; i <= currentLap; ++i) {
            double lapDegradation = computeLapDegradation(tire, trackTemp);
            totalDegradation += lapDegradation;

            if (totalDegradation >= 100.00) {
                totalDegradation = 100.00;
                pitStopLap = i;
                break;
            }
        }

        remainingLife = 100.0 - totalDegradation;
        printLapStatus(currentLap, totalLaps, totalDegradation, remainingLife);

        if (pitStopLap > 0) {
            cout << " Tire worn out on lap " << pitStopLap << "! PIT STOP necessary\n";
            return;  
        }

        if (currentLap < totalLaps) {
            printForecast(tire, currentLap, totalLaps, trackTemp, totalDegradation);
        }
        else {
            cout << " The race is over! Final tire life: " << remainingLife << "%\n";
        }
    }

    int suggestPitLap(const Tire& tire, int trackTemp, int totalLaps, int currentLap) {
        if (totalLaps <= 0 || currentLap < 0 || currentLap > totalLaps) {
            cout << "Invalid number of laps for pit stop suggestion\n";
            return -1;
        }

        double totalDegradation = 0.0;

        // przejechane okrazenie
        for (int i = 1; i <= currentLap; ++i) {
            totalDegradation += computeLapDegradation(tire, trackTemp);
        }

        // kiedy jest idealnie, zeby zrobic pitstop
        for (int i = currentLap + 1; i <= totalLaps; ++i) {
            totalDegradation += computeLapDegradation(tire, trackTemp);
            double remainingLife = 100.0 - totalDegradation;

            if (remainingLife <= 20.0 && remainingLife >= 10.0) {
                return i;
            }

            if (remainingLife < 10.0) {
                break; 
            }
        }
        return -1;
    }

    Tire suggestNextTire(int lapsRemaining, int trackTemp) {
        if (lapsRemaining >= 15) {
            return { "Hard", 3.0, 80 };
        }
        else if (trackTemp > 35) {
            return { "Medium", 4.0, 85 };
        }
        else {
            return { "Soft", 5.0, 90 };
        }
    }


    void runFullRaceSimulation(Tire tire, int totalLaps, int trackTemp) {
        int currentLap = 1;
        bool raceOngoing = true;

        while (raceOngoing) {
            cout << "\n=== Simulating from lap " << currentLap << " / " << totalLaps << " ===\n";

            calculateRemainingTireLife(tire, totalLaps, currentLap, trackTemp);

            int pitLap = suggestPitLap(tire, trackTemp, totalLaps, currentLap);

            if (pitLap == -1 || pitLap >= totalLaps) {
                cout << "\n Race completed or no pit stop needed \n";
                break;
            }

            cout << "\n>>> Suggested PIT STOP on lap: " << pitLap;

            int lapsRemaining = totalLaps - pitLap;
            Tire nextTire = suggestNextTire(lapsRemaining, trackTemp);
            cout << "\n>>> Recommended tire after PIT STOP: "
                << nextTire.type << " (Degradation: "
                << nextTire.baseDegradation << "%, Optimal temp: "
                << nextTire.optimalTemp << "°C)\n";

            char confirm;
            cout << "Do you want to switch to this tire and countinue? (y/n): ";
            cin >> confirm;

            if (confirm == 'y' || confirm == 'Y') {
                tire = nextTire;
                currentLap = pitLap;
            }
            else {
                cout << "Simulation stopped by user\n";
                raceOngoing = false;
            }

            if (currentLap >= totalLaps) {
                cout << "Race finished \n";
                break;
            }
        }
    }

}