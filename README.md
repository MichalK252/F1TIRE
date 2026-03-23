# F1 Tire Simulator

## Overview

F1 Tire Simulator is a console-based application that simulates Formula 1 tire wear and race conditions. The simulation allows users to select a race track, initial tire type, track temperature, and number of laps to predict tire degradation and lap times. It also features realistic tire wear rates and recommends optimal pit stop laps. Simulation results can be saved to a CSV file for analytical purposes.

---

## Features

- Choose from a list of F1 Grand Prix tracks.
- Select starting tire type and set track temperature.
- Simulate tire wear and performance over a race distance with realistic tire degradation logic.
- Receive optimal pit stop lap recommendations based on real-time tire wear.
- Maintain user control over new tire choices during pit stops.
- Save simulation results with detailed data (track, temperature, laps, tire wear, best lap, pit stop lap, date) to a CSV file.
- CSV files include headers for easy readability.
- Console help support (`--help` argument).

---

## Getting Started

### Prerequisites

- A C++ compiler supporting C++11 or higher.
- CMake (optional, for cross-platform builds).
- Windows or Linux environment.

### Installation

**Using Visual Studio (Windows)**
1. Clone or download the repository.
2. Open the `F1TIRE.sln` solution file in Visual Studio.
3. Build the solution (`Build > Build Solution` or `Ctrl + Shift + B`).
4. Run the project directly from Visual Studio.

**Using CMake (Command Line)**
1. Clone or download the repository.
2. Open a terminal or command prompt in the project root folder.
3. Create a build directory and navigate into it:
   ```bash
   mkdir build
   cd build
   ```
4. Generate the build files:
   ```bash
   cmake ..
   ```
5. Compile the project:
   ```bash
   cmake --build .
   ```
6. Run the resulting executable from the build directory.
