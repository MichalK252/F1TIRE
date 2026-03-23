#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <limits>
#include "Simulation.h"
#include "TireMenu.h"
#include "SimulationFlow.h"

using namespace std;

namespace F1Sim {

    static const double PIT_LIFE_THRESHOLD  = 30.0;
    static const double PIT_URGENT_THRESHOLD = 15.0;

    struct LapRecord {
        int    lap;
        double wearPct;
        double lifePct;
        double lapTime;
        bool   pitStop;
        string tireType;
    };

    static const Tire TIRE_OPTIONS[5] = {
        { "Soft",         4.0, 45 },
        { "Medium",       2.8, 38 },
        { "Hard",         2.0, 30 },
        { "Intermediate", 2.5, 20 },
        { "Wet",          2.2, 10 },
    };

    static Tire chooseTireDuringPitStop(int lapsRemaining, int trackTemp) {
        Tire recommended = suggestNextTire(lapsRemaining, trackTemp);

        cout << "\n  +----- PIT STOP MENU -------------------------------------+\n";
        cout << "  | Laps remaining: " << lapsRemaining << "\n";
        cout << "  | Recommended   : " << recommended.type << "\n";
        cout << "  |-------------------------------------------------------+\n";
        cout << "  | Choose tire:\n";

        for (int i = 0; i < 5; i++) {
            const Tire& t = TIRE_OPTIONS[i];
            int estLaps   = (int)(100.0 / t.baseDegradation);
            bool isRec    = (t.type == recommended.type);

            cout << "  |  " << (i + 1) << ". "
                 << left << setw(14) << t.type
                 << "~" << setw(3) << estLaps << " laps"
                 << "  (" << t.baseDegradation << "%/lap)";
            if (isRec) cout << "  <-- RECOMMENDED";
            cout << "\n";
        }

        cout << "  |  0. Skip pit stop (continue on current tires)\n";
        cout << "  +-------------------------------------------------------+\n";

        int choice = -1;
        while (choice < 0 || choice > 5) {
            cout << "  Your choice (0-5): ";
            if (!(cin >> choice) || choice < 0 || choice > 5) {
                cin.clear();
                choice = -1;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "\n";

        if (choice >= 1 && choice <= 5)
            return TIRE_OPTIONS[choice - 1];

        return { "", 0.0, 0 };
    }

    SimulationResult runSimulationLoop(Tire& tire, int trackTemp, int totalLaps, double baseLapTime) {
        SimulationResult result;
        result.finalTireWear     = 0.0;
        result.bestLapTime       = 1e9;
        result.recommendedPitLap = -1;
        result.actualPitLap      = -1;
        result.finalTireType     = tire.type;

        double totalDegradation = 0.0;
        vector<LapRecord> history;

        cout << "\n";
        cout << "==========================================================\n";
        cout << "          F1 TIRE SIMULATION\n";
        cout << "  Track temp : " << trackTemp << " C\n";
        cout << "  Laps       : " << totalLaps << "\n";
        cout << "  Start tire : " << tire.type << "\n";
        cout << "  Base lap   : " << fixed << setprecision(3) << baseLapTime << " s\n";
        cout << "==========================================================\n\n";

        cout << left
             << setw(6)  << "Lap"
             << setw(14) << "Tire"
             << setw(10) << "Wear %"
             << setw(10) << "Life %"
             << setw(12) << "Lap time"
             << "Note\n";
        cout << string(65, '-') << "\n";

        for (int lap = 1; lap <= totalLaps; lap++) {

            double lapDeg = computeLapDegradation(tire, trackTemp, totalDegradation);
            totalDegradation += lapDeg;
            if (totalDegradation > 100.0) totalDegradation = 100.0;

            double lifeLeft = 100.0 - totalDegradation;
            double lapTime  = computeLapTime(tire, totalDegradation, baseLapTime);
            if (lapTime < result.bestLapTime) result.bestLapTime = lapTime;

            string note = "";
            if      (totalDegradation >= 100.0)            note = "!! TIRE BLOWN !!";
            else if (lifeLeft <= PIT_URGENT_THRESHOLD)     note = "!!! PIT STOP NOW !!!";
            else if (lifeLeft <= PIT_LIFE_THRESHOLD)       note = ">>> PIT STOP SUGGESTED";
            else if (lifeLeft <= 40.0)                     note = "~ wear increasing";

            cout << left
                 << setw(6)  << lap
                 << setw(14) << tire.type
                 << fixed << setprecision(1)
                 << setw(10) << totalDegradation
                 << setw(10) << max(0.0, lifeLeft)
                 << setprecision(3) << setw(12) << lapTime
                 << note << "\n";

            bool didPit = false;

            if (totalDegradation >= 100.0) {
                if (lap >= totalLaps) {
                    cout << "\n  Race finished (tires expiered).\n";
                    history.push_back({ lap, totalDegradation, 0.0, lapTime, false, tire.type });
                    break;
                }

                cout << "\n  *** TIRE BLOWN on lap " << lap << " ***\n";

                Tire chosen = chooseTireDuringPitStop(totalLaps - lap, trackTemp);
                if (!chosen.type.empty()) {
                    result.actualPitLap  = lap;
                    tire                 = chosen;
                    result.finalTireType = tire.type;
                    totalDegradation     = 0.0;
                    didPit               = true;
                    cout << "  >>> Pit stop done! Mounted: " << tire.type << "\n\n";

                    cout << left
                         << setw(6)  << "Lap"
                         << setw(14) << "Tire"
                         << setw(10) << "Wear %"
                         << setw(10) << "Life %"
                         << setw(12) << "Lap time"
                         << "Note\n";
                    cout << string(65, '-') << "\n";
                } else {
                    cout << "  Skipping pit stop (risky!).\n\n";
                }

                history.push_back({ lap, totalDegradation, lifeLeft, lapTime, didPit, tire.type });
                continue;
            }

            if (lifeLeft <= PIT_LIFE_THRESHOLD && lap < totalLaps) {
                if (result.recommendedPitLap == -1)
                    result.recommendedPitLap = lap;

                Tire chosen = chooseTireDuringPitStop(totalLaps - lap, trackTemp);

                if (!chosen.type.empty()) {
                    result.actualPitLap  = lap;
                    tire                 = chosen;
                    result.finalTireType = tire.type;
                    totalDegradation     = 0.0;
                    didPit               = true;
                    cout << "  >>> Pit stop done! Mounted: " << tire.type << "\n\n";

                    cout << left
                         << setw(6)  << "Lap"
                         << setw(14) << "Tire"
                         << setw(10) << "Wear %"
                         << setw(10) << "Life %"
                         << setw(12) << "Lap time"
                         << "Note\n";
                    cout << string(65, '-') << "\n";
                } else {
                    cout << "  Continuing on worn tires.\n\n";
                }
            }

            history.push_back({ lap, totalDegradation, lifeLeft, lapTime, didPit, tire.type });
        }

        result.finalTireWear = totalDegradation;
        if (result.bestLapTime >= 1e8) result.bestLapTime = baseLapTime;

        cout << "\n" << string(65, '=') << "\n";
        cout << "  RACE SUMMARY\n";
        cout << string(65, '=') << "\n";
        cout << "  Best lap time    : " << fixed << setprecision(3) << result.bestLapTime << " s\n";
        cout << "  Final tire wear  : " << setprecision(1) << result.finalTireWear << " %\n";
        cout << "  Final tire type  : " << result.finalTireType << "\n";
        cout << "  Pit stop on lap  : ";
        if (result.actualPitLap > 0) cout << result.actualPitLap << "\n";
        else                         cout << "none (tires lasted full race)\n";

        cout << "\n  PIT STOP LOG:\n";
        bool anyPit = false;
        for (const LapRecord& r : history) {
            if (r.pitStop) {
                cout << "    Lap " << r.lap << " -> switched to " << r.tireType << "\n";
                anyPit = true;
            }
        }
        if (!anyPit) cout << "    No pit stops.\n";
        cout << string(65, '=') << "\n";

        return result;
    }
}
