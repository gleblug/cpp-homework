#include <iostream>

using namespace std;

int main() {
  // Declaring varibles
  int x;
  int y;

  // Input values
  cout << "Enter x, y (integers) and this program will swap them:" << endl
    << "x = ";
  cin >> x;

  cout << "y = ";
  cin >> y;

  // Swapping algorithm
  y += x;
  x -= y;
  y += x;
  x = -x;

  // Output values
  cout << endl
    << "x = " << x << endl
    << "y = " << y << endl;

  // Finish program successfully
  return EXIT_SUCCESS;
}
