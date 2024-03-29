#include <iostream>
#include "Fraction.hpp"

int main(int argc, char const *argv[]) {

  math::Fraction a;
  math::Fraction b;

  std::cout << "Input two fractions" << '\n'
            << "a = ";
  std::cin >> a;

  std::cout << "b = ";
  std::cin >> b;

  std::cout << "--------------------"                         << '\n'
            << "a + b = "             << a + b                << '\n'
            << "a - b = "             << a - b                << '\n'
            << "a * b = "             << a * b                << '\n'
            << "a / b = "             << a / b                << '\n'
            << "--------------------"                         << '\n'
            << "reverse a =         " << a.reverse()          << '\n'
            << "integer part a =    " << a.integer_part()     << '\n'
            << "fractional part a = " << a.fractional_part()  << '\n'
            << "--------------------"                         << '\n'
            << "a == b ? " << std::boolalpha << (a == b)      << '\n'
            << "a != b ? " << std::boolalpha << (a != b)      << '\n'
            << "a > b  ? " << std::boolalpha << (a > b)       << '\n'
            << "a < b  ? " << std::boolalpha << (a < b)       << '\n'
            << "--------------------"                         << '\n'
            << "a++ "                 << a++                  << '\n'
            << "a   "                 << a                    << '\n'
            << "--a "                 << --a                  << '\n'
            << "a-- "                 << a--                  << '\n'
            << "a   "                 << a                    << std::endl;

  return 0;
}
