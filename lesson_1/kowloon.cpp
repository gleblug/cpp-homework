#include <iostream>
#include <iomanip>

using namespace std;

int main() {
  // Constants
  const size_t FIELD_WIDTH = 25;
  const char PLACEHOLDER = '.';

  // Declaring variables
  string productsName;
  int productsPrice;
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

  cout << left << "Price:"
      << setw(FIELD_WIDTH - 6) << setfill(PLACEHOLDER)
      << setw(8) << setfill('0')
      << right << hex << uppercase << productsPrice
      << endl;

  cout << left << "Has cash-back:"
      << setw(FIELD_WIDTH - 14) << setfill(PLACEHOLDER)
      << right << boolalpha << cashbackAvailable
      << endl;

  cout << left << "Max temperature:"
      << setw(FIELD_WIDTH - 16) << setfill(PLACEHOLDER) << dec
      << right << showpos << maxTemperature
      << endl;

  // Finish program
  return EXIT_SUCCESS;

}
