#pragma once

#include "TireMenu.h"

namespace F1Sim {

    // oblicza degradacje opony na jedno okrazenie
    double computeLapDegradation(const Tire& tire, int trackTemp);

    // wypisuje aktualny status zuzycia opony
    void printLapStatus(int currentLap, int totalLaps, double totalDegradation, double remainingLife);

    // wypisuje prognoze degradacji na reszte wyscigu
    void printForecast(const Tire& tire, int currentLap, int totalLaps, int trackTemp, double totalDegradation);

    // oblicza zuzycie opony i symuluje reszte wyscigu
    void calculateRemainingTireLife(Tire& tire, int totalLaps, int currentLap, int trackTemp);

    int suggestPitLap(const Tire& tire, int trackTemp, int totalLaps, int currentLap);

    Tire suggestNextTire(int lapsRemaining, int trackTemp);

    void runFullRaceSimulation(Tire tire, int totalLaps, int trackTemp);

}
