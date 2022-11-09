#include <iostream>
#include "Fraction.hpp"

int main(int argc, char const *argv[]) {
  try
  {
    math::Fraction a;
    math::Fraction b;

    std::cout << "Input two fractions" << '\n'
              << "a = ";
    std::cin >> a;

    std::cout << "b = ";
    std::cin >> b;

    std::cout << "--------------------" << '\n'
              << "a + b = " << a + b << '\n'
              << "a - b = " << a - b << '\n'
              << "a * b = " << a * b << '\n'
              << "a / b = " << a / b << '\n'
              << "--------------------" << '\n'
              << "reverse a =         " << a.reverse() << '\n'
              << "integer part a =    " << a.integer_part() << '\n'
              << "fractional part a = " << a.fractional_part() << '\n'
              << "--------------------" << '\n'
              << "a == b ? " << std::boolalpha << (a == b) << '\n'
              << "a != b ? " << std::boolalpha << (a != b) << '\n'
              << "a > b  ? " << std::boolalpha << (a > b) << '\n'
              << "a < b  ? " << std::boolalpha << (a < b) << '\n'
              << "--------------------" << '\n'
              << "a++ " << a++ << '\n'
              << "a   " << a << '\n'
              << "--a " << --a << '\n'
              << "a-- " << a-- << '\n'
              << "a   " << a << std::endl;
  }
  catch(const std::exception& e)
  {
    std::cerr << "\x1B[31m"
              << "ERROR: " << e.what() << "\033[0m\n";
    exit(EXIT_FAILURE);
  }
  catch(...)
  {
    std::cerr << "\x1B[31m"
              << "UNKNOWN ERROR"
              << "\033[0m\n";
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
