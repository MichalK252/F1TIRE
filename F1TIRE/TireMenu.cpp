#include "TireMenu.h"
#include <iostream>
using namespace std;

namespace F1Sim {

	void showTireOptions() {
		cout << R"(
   _____ _    _  ____   ____   _____ ______   _______ _____ _____  ______ 
  / ____| |  | |/ __ \ / __ \ / ____|  ____| |__   __|_   _|  __ \|  ____|
 | |    | |__| | |  | | |  | | (___ | |__       | |    | | | |__) | |__   
 | |    |  __  | |  | | |  | |\___ \|  __|      | |    | | |  _  /|  __|  
 | |____| |  | | |__| | |__| |____) | |____     | |   _| |_| | \ \| |____ 
  \_____|_|  |_|\____/ \____/|_____/|______|    |_|  |_____|_|  \_\______|
                                                                          
                                                                          
	)" << endl;
		cout << "1. Soft (The fastest)\n";
		cout << "2. Medium (Balanced)\n";
		cout << "3. Hard (Slower)\n";
		cout << "4. Intermediate (Wet)\n";
		cout << "5. Wet (Very wet)\n";
	}
	
	Tire chooseTire() {
		int choice;
		showTireOptions();

		do {
			cout << "Your choice: ";
			cin >> choice;
		} while (choice < 1 || choice > 5);

		Tire selectedTire;

		switch (choice)
		{
		case 1:
			selectedTire = { "Soft", 60, 90 };
			break;
		case 2:
			selectedTire = { "Medium", 75, 85 };
			break;
		case 3:
			selectedTire = { "Hard", 90, 80 };
			break;
		case 4:
			selectedTire = { "Intermediate", 70, 75 };
			break;
		case 5:
			selectedTire = { "Wet", 65, 70 };
			break;
		}
		cout << "\nSelected tire: " << selectedTire.type << "\n";
		return selectedTire;
	}
}