# F1 Tire Simulator

## Overview

F1 Tire Simulator is a console-based application that simulates Formula 1 tire wear and race conditions. The simulation allows users to select a race track, tire type, track temperature, and number of laps to predict tire degradation, best lap times, and recommend the optimal lap for pit stops. The simulation results can be saved to a CSV file for further analysis.

---

## Features

- Choose from a list of F1 Grand Prix tracks.
- Select tire type and set track temperature.
- Simulate tire wear and performance over a race distance.
- Recommend the best pit stop lap based on tire wear.
- Save simulation results with detailed data (track, temperature, laps, tire wear, best lap, pit stop lap, date) to a CSV file.
- CSV files include headers for easy readability.
- Console help support (`--help` argument).

---

## Getting Started

### Prerequisites

- A C++ compiler supporting C++11 or higher.
- CMake (optional, if you use CMake to build).
- Windows or Linux environment.

---

### Building the Project

#### Using Visual Studio (Windows)

1. Open the `.sln` file in Visual Studio.
2. Build the project (choose Debug or Release).
3. The executable `F1TIRE.exe` will be created in the `Debug` or `Release` folder.

#### Using CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .
