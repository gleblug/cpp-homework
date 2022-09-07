#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

// Function which calculate the discriminant
double discriminantCalculator(double a, double b, double c) {
  double discriminant;
  discriminant = b * b - 4 * a * c;

  return discriminant;
}

int main() {
  // Constants
  const size_t FIELD_WIDTH = 19;

  // Declaring variables
  double a;
  double b;
  double c;
  double x1;
  double x2;
  double discriminant;

  // Program welcome and input coefficients
  cout << "Welcome to quadratic equation solver!" << endl
    << "Please, enter the coefficients of eqution: " << endl
    << "a = ";
  cin >> a;

  cout << "b = ";
  cin >> b;

  cout << "c = ";
  cin >> c;

  cout << endl;

  // Calculate the discriminant
  discriminant = discriminantCalculator(a, b, c);

  // Calculate and output the solution
  if (a == 0 && b != 0) {
    // Case with one solution (a == 0)
    x1 = -c / b;

    cout << "There are one solution:" << endl
     << "x = " << setw(FIELD_WIDTH) << right << x1 << endl;

  } else if (a == 0 && b == 0) {
    // Case with a == 0 and b == 0
    if (c == 0) {
      cout << "There are an infinite number of solutions!" << endl;
    } else {
      cout << "There are no solutions!" << endl;
    };

  } else if (discriminant < 0) {
    // Case with no solutions
    cout << "There are no solutions!" << endl;

  } else if (discriminant == 0) {
    // Case with one solution
    x1 = (-b + sqrt(discriminant)) / (2 * a);

    cout << "There are one solution:" << endl
      << "x = " << setw(FIELD_WIDTH) << right << x1 << endl;

  } else {
    // Case with two solutions
    x1 = (-b + sqrt(discriminant)) / (2 * a);
    x2 = (-b - sqrt(discriminant)) / (2 * a);

    cout << "There are two solutions:" << endl
      << "x1 = " << setw(FIELD_WIDTH) << right << x1 << endl
      << "x2 = " << setw(FIELD_WIDTH) << right << x2 << endl;
  };

  // Finish program
  return EXIT_SUCCESS;
}
