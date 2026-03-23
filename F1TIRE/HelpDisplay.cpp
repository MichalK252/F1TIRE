#include "HelpDisplay.h"
#include <iostream>
#include <string>

namespace F1Sim {
    void showHelp() {
        std::cout << "F1TIRE - Formula 1 Tire Simulation Tool\n";
        std::cout << "========================================\n\n";
        std::cout << "Usage:\n";
        std::cout << "  F1TIRE.exe [laps] [track_temperature]\n";
        std::cout << "  F1TIRE.exe --help\n\n";
        std::cout << "Arguments:\n";
        std::cout << "  laps              Number of laps (1-150)\n";
        std::cout << "  track_temperature Track temperature in Celsius (-20 to 100)\n";
        std::cout << "  --help           Show this help message\n\n";
        std::cout << "Description:\n";
        std::cout << "  F1TIRE is a simulation tool that helps predict tire wear and strategy\n";
        std::cout << "  for Formula 1 races. It allows you to:\n";
        std::cout << "  - Select a race track from the F1 calendar\n";
        std::cout << "  - Choose tire compounds\n";
        std::cout << "  - Simulate tire degradation\n";
        std::cout << "  - Get pit stop recommendations\n\n";
        std::cout << "Examples:\n";
        std::cout << "  F1TIRE.exe              # Run with interactive input\n";
        std::cout << "  F1TIRE.exe 58 35        # 58 laps, 35�C track temperature\n";
    }

    bool isHelpRequested(int argc, char* argv[]) {
        return (argc > 1 && std::string(argv[1]) == "--help");
    }
}
