#include <iostream>
#include "Fraction.hpp"

int main(int argc, char const *argv[]) {

  math::Fraction a;
  // math::Fraction b;

  std::cin >> a;
  // std::cin >> b;

  std::cout << a.get_numerator() << '\n' << a.get_denominator() << '\n';

  return 0;
}
