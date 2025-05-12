#pragma once
#include <string>
#include <vector>

namespace F1Sim {
	void showRaces(const std::vector<std::string>& races);
	int getRaceSelection(int raceCount);
}