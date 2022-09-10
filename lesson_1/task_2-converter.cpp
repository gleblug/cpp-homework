#include <iostream>

using namespace std;

int main() {
  // Constants
  const double N_TO_DIN = 1e5;
  const double J_TO_ERG = 1e7;
  const double COUL_TO_CGS = 3 * 1e9;

  // Declaring variables
  size_t unitType;
  double unitValue;

  // Welcome output and input type
  cout << "Welcome to the SI -> CGS unit converter!" << endl
    << "Choose which unit you want to convert:" << endl
    << "Force: newton -> dyne (1)" << endl
    << "Work: joule -> erg (2)" << endl
    << "Charge: coulomb -> CGS-unit (3)" << endl;
  cin >> unitType;

  // Input value
  cout << endl << "Enter the number for the conversion (separator is a dot):" << endl;
  cin >> unitValue;

  // Considering several cases
  cout << endl << "Result: ";
  switch (unitType) {
    case 1:
      // Newton to dyne
      cout << unitValue * N_TO_DIN << " dyne" << endl;
      break;
    case 2:
      // Joule to erg
      cout << unitValue * J_TO_ERG << " erg" << endl;
      break;
    case 3:
      // Coulomb to CGS-unit
      cout << unitValue * COUL_TO_CGS << " CGS-unit" << endl;
      break;
    default:
      // Case if type input is incorrect
      cout << "An invalid convertion type was selected!" << endl;
      break;
  };

  // Finish program successfull
  return EXIT_SUCCESS;
}
