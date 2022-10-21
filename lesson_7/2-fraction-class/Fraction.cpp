#include "Fraction.hpp"
#include <string>
#include <cmath>

namespace math {

  Fraction::Fraction(int number):
    numerator(std::abs(number)),
    denominator(1)
  {
    minus = (number < 0);
  }

  Fraction::Fraction(double number)
  {
    minus = (number < 0);
    number = std::abs(number);

    int dec = 1;

    while (number - (int)number > 0) {
      dec *= 10;
      number *= 10;
    }

    numerator = number;
    denominator = dec;

    simplify();
  }

  Fraction::Fraction(int num, int den)
  {
    minus = (num * den < 0);
    numerator = std::abs(num);
    denominator = std::abs(den);

    simplify();
  }

}
