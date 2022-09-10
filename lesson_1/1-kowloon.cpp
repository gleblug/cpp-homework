#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

int main() {
  // Constants
  const size_t FIELD_WIDTH = 25;
  const char PLACEHOLDER = '.';

  // Declaring variables
  string productsName;
  int productsPrice;
  ostringstream strProductsPrice;
  bool cashbackAvailable;
  int maxTemperature;

  // Getting data
  cout << "Product's name: ";
  cin >> productsName;

  cout << "Product's price: ";
  cin >> productsPrice;

  cout << "Is cash-back available for this product? (true/false) ";
  cin >> boolalpha >> cashbackAvailable;

  cout << "Maximum storing temperature: ";
  cin >> maxTemperature;

  // Output data
  cout << '\n'
      << productsName
      << endl;

  strProductsPrice << setw(8) << setfill('0')
      << right << hex << uppercase << productsPrice;
  cout << left << "Price:"
      << setw(FIELD_WIDTH - 6) << setfill(PLACEHOLDER)
      << right << strProductsPrice.str()
      << endl

      << left << "Has cash-back:"
      << setw(FIELD_WIDTH - 14) << setfill(PLACEHOLDER)
      << right << boolalpha << cashbackAvailable
      << endl

      << left << "Max temperature:"
      << setw(FIELD_WIDTH - 16) << setfill(PLACEHOLDER)
      << right << dec << showpos << maxTemperature
      << endl;

  // Finish program
  return EXIT_SUCCESS;

}
