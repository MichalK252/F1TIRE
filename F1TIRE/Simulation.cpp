#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Simulation.h"
#include "TireMenu.h"

#define RESET  "\033[0m"
#define YELLOW "\033[33m"
#define RED    "\033[31m"
#define GREEN  "\033[32m"
#define CYAN   "\033[36m"

using namespace std;

namespace F1Sim {

    const double TEMP_THRESHOLD     = 10.0;

    const double CRITICAL_WEAR      = 15.0;
    const double EARLY_WARNING_WEAR = 30.0;

    double computeLapDegradation(const Tire& tire, int trackTemp, double currentWear) {
        double lapDeg = tire.baseDegradation;

        double tempDiff = fabs((double)(trackTemp - tire.optimalTemp));
        if (tempDiff > TEMP_THRESHOLD) {
            double over  = tempDiff - TEMP_THRESHOLD;
            double penalty = 1.0 + (over / 60.0);
            if (penalty > 1.4) penalty = 1.4;
            lapDeg *= penalty;
        }

        double wearFactor = 1.0 + (currentWear / 100.0) * 0.25;
        lapDeg *= wearFactor;

        return lapDeg;
    }

    double computeLapTime(const Tire& tire, double tireWear, double baseLapTime) {
        double tireBonus = 0.0;
        if      (tire.type == "Soft")         tireBonus = -0.5;
        else if (tire.type == "Medium")       tireBonus = -0.25;
        else if (tire.type == "Hard")         tireBonus =  0.0;
        else if (tire.type == "Intermediate") tireBonus =  1.5;
        else if (tire.type == "Wet")          tireBonus =  3.0;

        double wearPenalty = (tireWear / 100.0) * 0.03 * baseLapTime;
        return baseLapTime + tireBonus + wearPenalty;
    }

    void printLapStatus(int currentLap, int totalLaps, double totalDegradation,
                        double remainingLife, double lapTime) {
        const char* color = GREEN;
        if      (remainingLife <= CRITICAL_WEAR)      color = RED;
        else if (remainingLife <= EARLY_WARNING_WEAR) color = YELLOW;

        cout << left
             << setw(6)  << currentLap
             << setw(10) << ""
             << color
             << setw(12) << fixed << setprecision(1) << totalDegradation
             << setw(12) << remainingLife
             << RESET
             << setprecision(3) << lapTime;
    }

    void printForecast(const Tire& tire, int currentLap, int totalLaps,
                       int trackTemp, double totalDegradation) {
        double forecastDeg = totalDegradation;
        int    pitStopLap  = -1;

        cout << "\n" << YELLOW << "--- Forecast from lap " << currentLap
             << " to " << totalLaps << " ---" << RESET << "\n";

        for (int i = currentLap + 1; i <= totalLaps; i++) {
            forecastDeg += computeLapDegradation(tire, trackTemp, forecastDeg);
            double rem = 100.0 - forecastDeg;
            if (rem < 0.0) rem = 0.0;

            cout << "  Lap " << setw(3) << i << ": Life "
                 << fixed << setprecision(1) << rem << "%";

            if (forecastDeg >= 100.0 && pitStopLap < 0) {
                pitStopLap = i;
                cout << RED << "  !! FAILURE !!" << RESET;
            }
            cout << "\n";
            if (forecastDeg >= 100.0) break;
        }

        if (pitStopLap == -1)
            cout << GREEN << "  -> Tire should last until end.\n" << RESET;
        else
            cout << RED << "  -> Failure predicted on lap " << pitStopLap << "\n" << RESET;
    }

    int suggestPitLap(const Tire& tire, int trackTemp, int totalLaps,
                      int currentLap, double currentWear) {
        if (totalLaps <= 0 || currentLap < 0 || currentLap > totalLaps) return -1;

        double deg = currentWear;
        for (int i = currentLap + 1; i <= totalLaps; ++i) {
            deg += computeLapDegradation(tire, trackTemp, deg);
            double remaining = 100.0 - deg;

            if (remaining <= EARLY_WARNING_WEAR) {

                int safetyBuffer = (remaining <= CRITICAL_WEAR) ? 0 : 2;
                return (std::max)(currentLap + 1, i - safetyBuffer);
            }
            if (deg >= 100.0) {
                return (std::max)(currentLap + 1, i - 1);
            }
        }
        return -1;
    }

    Tire suggestNextTire(int lapsRemaining, int trackTemp) {
        if (lapsRemaining >= 25) {
            return { "Hard", 2.0, 30 };
        } else if (lapsRemaining >= 12) {
            return (trackTemp > 38) ? Tire{ "Medium", 2.8, 38 }
                                    : Tire{ "Hard",   2.0, 30 };
        } else {
            return (trackTemp > 40) ? Tire{ "Medium", 2.8, 38 }
                                    : Tire{ "Soft",   4.0, 45 };
        }
    }

    Tire suggestBestTireOption(int trackTemp) {
        vector<Tire> options = {
            { "Soft",         4.0, 45 },
            { "Medium",       2.8, 38 },
            { "Hard",         2.0, 30 },
            { "Intermediate", 2.5, 20 },
            { "Wet",          2.2, 10 }
        };

        sort(options.begin(), options.end(), [&](const Tire& a, const Tire& b) {
            double da = a.baseDegradation;
            double db = b.baseDegradation;
            if (fabs((double)(trackTemp - a.optimalTemp)) > TEMP_THRESHOLD)
                da *= 1.2;
            if (fabs((double)(trackTemp - b.optimalTemp)) > TEMP_THRESHOLD)
                db *= 1.2;
            return da < db;
        });

        cout << "\n>>> Available tire options (sorted by durability at " << trackTemp << " C):\n";
        for (const Tire& t : options) {
            double diff = fabs((double)(trackTemp - t.optimalTemp));
            const char* fit = (diff <= TEMP_THRESHOLD) ? GREEN
                            : (diff <= 20)              ? YELLOW : RED;
            cout << " - " << fit << t.type << RESET
                 << " (base " << t.baseDegradation << "%/lap"
                 << ", opt temp " << t.optimalTemp << " C";
            if (diff <= TEMP_THRESHOLD) cout << GREEN << " [IDEAL]" << RESET;
            cout << ")\n";
        }

        return options[0];
    }

}
