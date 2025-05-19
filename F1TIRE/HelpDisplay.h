#pragma once
#pragma once
#ifndef HELP_DISPLAY_H
#define HELP_DISPLAY_H

namespace F1Sim {
    // Wyœwietla informacje pomocy dla programu
    void showHelp();

    // Sprawdza czy podano argument --help
    bool isHelpRequested(int argc, char* argv[]);
}

#endif // HELP_DISPLAY_H
