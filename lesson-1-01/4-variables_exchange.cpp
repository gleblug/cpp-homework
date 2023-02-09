#include <iostream>

using namespace std;

int main() {
  // Declaring varibles (every type!)
  int x;
  int y;

  // Input values
  cout << "Enter x, y (integers) and this program will swap them:" << endl
    << "x = ";
  cin >> x;

  cout << "y = ";
  cin >> y;

  // Swapping algorithm
  x = x ^ y;
  y = x ^ y;
  x = x ^ y;

  // Output values
  cout << endl
    << "x = " << x << endl
    << "y = " << y << endl;

  // Finish program successfully
  return EXIT_SUCCESS;
}
