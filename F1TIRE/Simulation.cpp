#include <iostream>
#include <iomanip>
#include "Simulation.h"

using namespace std;

namespace F1Sim {

	double computeLapDegration(const Tire& tire, int trackTemp) {
		double lapDegration = tire.baseDegradation;

		if (trackTemp < tire.optimalTemp - 5 || trackTemp > tire.optimalTemp + 5) {
			lapDegration *= 1.5;
		}

		return lapDegration;
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
				cout << "?? CRITICAL WEAR AND TEAR!"
			}
			cout << "\n";

			if (pitStopLap > 0 && i >= pitStopLap) {
				break;
			}
		}

		if (pitStopLap > 0) {
			cout << "\n?? PIT STOP ENDING on lap " << pitStopLap << "!\n";
		}
		else {
			double finalRemainingLife = 100.0 - forecastDegradation;
			if (finalRemainingLif)
		}
	}


}