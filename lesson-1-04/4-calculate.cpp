#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <cmath>

double calculate(double x, double y, std::function<double(double, double)> const& MATH_OPERATOR) {
  return MATH_OPERATOR(x, y);
}

int main(int argc, char const *argv[]) {

  // Const vector of lambdas
  const std::vector < std::function <double(double, double)> > MATH_OPERATORS{
    [](double x, double y){ return x + y;},
    [](double x, double y){ return x - y;},
    [](double x, double y){ return x / y;},
    [](double x, double y){ return x * y;},
    [](double x, double y){ return pow(x, y);},
  };

  const std::vector < std::vector < std::string > > DESCRIPTIONS {
    {"plus", "+"},
    {"minus", "-"},
    {"div", "/"},
    {"mul", "*"},
    {"exp", "^"},
  };

  // Declaring vars
  double x;
  double y;

  std::string userChoise;

  // User input (x and y)
  std::cout << "Input two float numbers: " << '\n'
    << "x = ";
  std::cin >> x;

  std::cout << "y = ";
  std::cin >> y;

  std::cout << std::endl;

  // Choose operator from list (or show them all)
  std::cout << "Choose operator from list (or calculate them all): ";
  for (auto const& DESCRIPTION: DESCRIPTIONS) {
    std::cout << DESCRIPTION.at(0) << ", ";
  }
  std::cout << "all." << std::endl;

  // Save user choise
  std::cin >> userChoise;
  std::cout << std::endl;

  // Output
  std::cout << "Result:" << '\n';

  // Main cycle
  for (size_t i = 0; i < MATH_OPERATORS.size(); i++)
  {
    if (userChoise == "all" || userChoise == DESCRIPTIONS.at(i).at(0)) {
      std::cout << "x " << DESCRIPTIONS.at(i).at(1) << " y = "
        << calculate(x, y, MATH_OPERATORS.at(i)) << std::endl;
    }
  }

  return 0;
}
