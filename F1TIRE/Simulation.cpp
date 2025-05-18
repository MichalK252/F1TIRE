#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

#include "Simulation.h"
#include "TireMenu.h"

#define RESET   "\033[0m"
#define YELLOW  "\033[33m"

#define DEGRADATION_MULTIPLIER 1.5
#define MAX_LAPS 200


typedef std::vector<F1Sim::Tire> TireList;

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

        cout << "\nDegradation forecast:\n";

        for (int i = currentLap + 1; i <= totalLaps; i++) {
            double lapDegradation = computeLapDegradation(tire, trackTemp);
            forecastDegradation += lapDegradation;
            double forecastRemaining = 100.0 - forecastDegradation;

            if (forecastRemaining < 0.0) forecastRemaining = 0.0;

            cout << "Lap " << i << ": Remaining " << forecastRemaining << "%";

            if (forecastDegradation >= 100.0 && pitStopLap < 0) {
                pitStopLap = i;
                cout << " - TIRE FAILURE";
            }
            cout << "\n";

            if (pitStopLap > 0 && i >= pitStopLap) {
                break;
            }
        }

        if (pitStopLap == -1) {
            cout << "\nTire should last until the end of the race.\n";
        }
        else {
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
        cout << "\nTire wear simulation: " << tire.type
            << " (optimal temp: " << tire.optimalTemp << "°C)\n";
        cout << "-------------------------------------------------\n";

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
            // Don't continue with forecast if tire is already worn out
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

        // Calculate degradation for completed laps
        for (int i = 1; i <= currentLap; ++i) {
            totalDegradation += computeLapDegradation(tire, trackTemp);
        }

        // If tire is already worn out, suggest immediate pit stop
        if (totalDegradation >= 100.0) {
            return currentLap;
        }

        // Find the optimal lap for a pit stop
        for (int i = currentLap + 1; i <= totalLaps; ++i) {
            totalDegradation += computeLapDegradation(tire, trackTemp);
            double remainingLife = 100.0 - totalDegradation;

            if (remainingLife <= 20.0 && remainingLife >= 10.0) {
                return i;
            }

            if (remainingLife < 10.0) {
                return i - 1; // Return the previous lap to avoid tire failure
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
        double totalDegradation = 0.0;
        int lastPitLap = 1;

        while (raceOngoing) {
            cout << "\n=== Simulating from lap " << currentLap << " / " << totalLaps << " ===\n";

            totalDegradation = 0.0;
            double remainingLife = 100.0;
            int tireFailureLap = -1;

            for (int i = lastPitLap; i <= currentLap; ++i) {
                double lapDegradation = computeLapDegradation(tire, trackTemp);
                totalDegradation += lapDegradation;

                if (totalDegradation >= 100.0 && tireFailureLap == -1) {
                    tireFailureLap = i;
                    totalDegradation = 100.0;
                }
            }


            remainingLife = 100.0 - totalDegradation;
            printLapStatus(currentLap, totalLaps, totalDegradation, remainingLife);

            if (tireFailureLap > 0 && tireFailureLap <= currentLap) {
                cout << " Tire worn out on lap " << tireFailureLap << "! PIT STOP necessary\n";

                if (currentLap == totalLaps) {
                    cout << "Race finished with worn tires!\n";
                    break;
                }

                char confirm;
                cout << "Do you want to make a pit stop now? (y/n): ";
                cin >> confirm;

                if (confirm == 'y' || confirm == 'Y') {
                    int lapsRemaining = totalLaps - currentLap;
                    Tire nextTire = suggestNextTire(lapsRemaining, trackTemp);
                    cout << "\n>>> Switched to " << nextTire.type << " tires (Degradation: "
                        << nextTire.baseDegradation << "%, Optimal temp: "
                        << nextTire.optimalTemp << "°C)\n";

                    tire = nextTire;
                    remainingLife = 100.00;
                    totalDegradation = 0.0;
                    continue;
                }
                else {
                    cout << "Warning: Continuing with worn tires is dangerous!\n";
                }
            }

            int pitLap = suggestPitLap(tire, trackTemp, totalLaps, currentLap);

            if (pitLap == -1) {
                cout << "\nTire should last until the end of the race.\n";

                char continueRace;
                cout << "Do you want to finish the race? (y/n): ";
                cin >> continueRace;

                if (continueRace == 'y' || continueRace == 'Y') {
                    cout << "Race simulation finished!\n";
                    break;
                }
                else {
                    cout << "Simulation stopped by user.\n";
                    break;
                }
            }
            else if (pitLap == currentLap) {
                cout << "\n>>> Suggested PIT STOP now (lap " << pitLap << ")\n";

                int lapsRemaining = totalLaps - pitLap;
                Tire nextTire = suggestNextTire(lapsRemaining, trackTemp);
                cout << ">>> Recommended tire: "
                    << nextTire.type << " (Degradation: "
                    << nextTire.baseDegradation << "%, Optimal temp: "
                    << nextTire.optimalTemp << "°C)\n";

                char confirm;
                cout << "Do you want to switch to this tire and continue? (y/n): ";
                cin >> confirm;

                if (confirm == 'y' || confirm == 'Y') {
                    tire = nextTire;
                    totalDegradation = 0.0;
                    remainingLife = 100.0;
                    lastPitLap = currentLap + 1;
                    continue;
                }
                else {
                    cout << "Continuing without pit stop.\n";
                }

                currentLap++;
            }
            else {
                cout << "\n" << YELLOW << ">>> Suggested PIT STOP on lap : " << pitLap << RESET << "\n";

                int lapsToRun;
                cout << "How many laps do you want to run? (0 to end simulation): ";
                cin >> lapsToRun;

                if (lapsToRun <= 0) {
                    cout << "Simulation stopped by user.\n";
                    break;
                }

                currentLap += lapsToRun;
                if (currentLap > totalLaps) {
                    currentLap = totalLaps;
                    cout << "Reached the end of the race.\n";
                }
            }

            if (currentLap >= totalLaps) {
                cout << "Race finished!\n";
                break;
            }
        }
    }

    Tire suggestBestTireOption(int trackTemp) {
        vector<Tire> options = {
            { "Soft", 5.0, 90 },
            { "Medium", 4.0, 85 },
            { "Hard", 3.0, 80 }
        };

        sort(options.begin(), options.end(), [](const Tire& a, const Tire& b) {
            return a.baseDegradation < b.baseDegradation;
            });

        cout << "\n>>> Available tire options (sorted by degradation efficiency):\n";
        for (const Tire& t : options) {
            cout << " - " << t.type
                << " (Degradation: " << t.baseDegradation << "%, Optimal Temp: " << t.optimalTemp << "°C)\n";
        }

        return options.front();
    }

}