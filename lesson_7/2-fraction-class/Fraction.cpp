#include "Fraction.hpp"
#include <string>
#include <cmath>
#include <iostream>
#include <numeric>

namespace math {

  Fraction::Fraction():
    numerator(1),
    denominator(1) {  }

  Fraction::Fraction(int number):
    numerator(number),
    denominator(1) {  }

  Fraction::Fraction(double number)
  {
    int dec = 1;

    while (std::abs(number - static_cast<int>(number)) > 0) {
      dec *= 10;
      number *= 10;
    }
    numerator = number;
    denominator = dec;

    simplify();
  }

  Fraction::Fraction(int num, int den)
  {
    if (!den) {
      error(Exceptions::division_by_zero);
    }
    numerator = (num * den < 0) ? -std::abs(num) : std::abs(num);
    denominator = std::abs(den);

    simplify();
  }

  std::ostream & operator<< (std::ostream & stream, const Fraction & frac)
  {
    stream << frac.numerator << '/' << frac.denominator;

    return stream;
  }

  std::istream & operator>> (std::istream & stream, Fraction & frac)
  {
    int num;
    int den;
    char delim;

    stream >> num >> delim >> den;
    
    frac.numerator = num;
    frac.denominator = den;

    if (!frac.denominator) error(Exceptions::division_by_zero);

    frac.simplify();

    return stream;
  }

  void Fraction::simplify()
  {
    int gcd = std::gcd(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
  }

  Fraction & Fraction::operator+=(const Fraction & other)
  {
    numerator = numerator * other.denominator + other.numerator * denominator;
    denominator = denominator * other.denominator;

    simplify();

    return (*this);
  }

  Fraction & Fraction::operator-= (const Fraction & other)
  {
    numerator = numerator * other.denominator - other.numerator * denominator;
    denominator = denominator * other.denominator;

    simplify();

    return (*this);
  }

  Fraction & Fraction::operator*= (const Fraction & other)
  {
    numerator *= other.numerator;
    denominator *= other.denominator;

    simplify();

    return (*this);
  }

  Fraction & Fraction::operator/= (const Fraction & other)
  {
    numerator *= other.denominator;
    denominator *= other.numerator;

    if (!denominator)
      error(Exceptions::division_by_zero);

    simplify();

    return (*this);
  }

  Fraction operator+ (const Fraction & lhs, const Fraction & rhs) { return Fraction(lhs) += rhs; }
  Fraction operator- (const Fraction & lhs, const Fraction & rhs) { return Fraction(lhs) -= rhs; }
  Fraction operator* (const Fraction & lhs, const Fraction & rhs) { return Fraction(lhs) *= rhs; }
  Fraction operator/ (const Fraction & lhs, const Fraction & rhs) { return Fraction(lhs) /= rhs; }

  bool operator== (const Fraction & lhs, const Fraction & rhs)
  {
    return (lhs.numerator == rhs.numerator) && (lhs.denominator == rhs.denominator);
  }
  bool operator!= (const Fraction & lhs, const Fraction & rhs)
  {
    return !(lhs == rhs);
  }

  bool operator< (const Fraction & lhs, const Fraction & rhs)
  {
    return (lhs.numerator * rhs.denominator) < (rhs.numerator * lhs.denominator);
  }
  bool operator> (const Fraction & lhs, const Fraction & rhs)
  {
    return !((lhs < rhs) || (lhs == rhs));
  }

  bool operator<= (const Fraction & lhs, const Fraction & rhs)
  {
    return !(lhs > rhs);
  }
  bool operator>= (const Fraction & lhs, const Fraction & rhs)
  {
    return !(lhs < rhs);
  }

  Fraction & Fraction::operator++()
  {
    (*this) += 1;

    return (*this);
  }
  Fraction & Fraction::operator--()
  {
    (*this) -= 1;

    return (*this);
  }

  Fraction Fraction::operator++(int)
  {
    Fraction temp(*this);
    ++(*this);

    return temp;
  }
  Fraction Fraction::operator--(int)
  {
    Fraction temp(*this);
    --(*this);

    return temp;
  }

  void error(Exceptions exception) {
   std::string error_message;
   switch (exception) {
     case Exceptions::division_by_zero:
       error_message = "Division by zero!";
       break;
     default:
       error_message = "Unknown exception.";
   }

   std::cerr << "\x1B[31m" << "ERROR: " << error_message << "\033[0m\n";
   exit(EXIT_FAILURE);
 }

}
