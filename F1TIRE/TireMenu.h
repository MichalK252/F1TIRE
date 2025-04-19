#pragma once
#include <string>

namespace F1Sim {

	struct Tire {
		std::string type;
		int durability;
		int optimalTemp;
	};

	void showTireOptions();
	Tire chooseTire();

}