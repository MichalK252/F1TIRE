#pragma once
#include <string>

namespace F1Sim {

    struct Tire {
        std::string type;
        double baseDegradation; 
        int optimalTemp;        
    };

    void showTireOptions();
    Tire chooseTire();

}
