#pragma once
#include "TireMenu.h"
#include "Simulation.h"

namespace F1Sim {
    SimulationResult runSimulationLoop(Tire& tire, int trackTemp, int totalLaps, double baseLapTime);
}
