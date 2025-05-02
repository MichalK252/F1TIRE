#pragma once

#include "TireMenu.h"

namespace F1Sim {

    // Oblicza degradacjê opony na jedno okr¹¿enie
    double computeLapDegradation(const Tire& tire, int trackTemp);

    // Wypisuje aktualny status zu¿ycia opony
    void printLapStatus(int currentLap, int totalLaps, double totalDegradation, double remainingLife);

    // Wypisuje prognozê degradacji na resztê wyœcigu
    void printForecast(const Tire& tire, int currentLap, int totalLaps, int trackTemp, double totalDegradation);

    // Oblicza zu¿ycie opony i symuluje resztê wyœcigu
    void calculateRemainingTireLife(Tire& tire, int totalLaps, int currentLap, int trackTemp);

}
