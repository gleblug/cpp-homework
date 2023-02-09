#include "Fraction.hpp"
#include "Exceptions.hpp"
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
    if (!den)
      throw division_by_zero();

    numerator = (num * den < 0) ? -std::abs(num) : std::abs(num);
    denominator = std::abs(den);

    simplify();
  }

  std::ostream & operator<< (std::ostream & stream, const Fraction & frac) noexcept
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

    if (delim != '/')
      throw invalid_value(delim);

    if (!frac.denominator)
      throw division_by_zero();

    frac.simplify();

    return stream;
  }

  void Fraction::simplify() noexcept
  {
    int gcd = std::gcd(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
  }

  Fraction & Fraction::operator+=(const Fraction & other) noexcept
  {
    numerator = numerator * other.denominator + other.numerator * denominator;
    denominator = denominator * other.denominator;

    simplify();

    return (*this);
  }

  Fraction & Fraction::operator-= (const Fraction & other) noexcept
  {
    numerator = numerator * other.denominator - other.numerator * denominator;
    denominator = denominator * other.denominator;

    simplify();

    return (*this);
  }

  Fraction & Fraction::operator*= (const Fraction & other) noexcept
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
      throw division_by_zero();

    simplify();

    return (*this);
  }

  Fraction operator+ (const Fraction & lhs, const Fraction & rhs) noexcept { return Fraction(lhs) += rhs; }
  Fraction operator- (const Fraction & lhs, const Fraction & rhs) noexcept { return Fraction(lhs) -= rhs; }
  Fraction operator* (const Fraction & lhs, const Fraction & rhs) noexcept { return Fraction(lhs) *= rhs; }
  Fraction operator/ (const Fraction & lhs, const Fraction & rhs) { return Fraction(lhs) /= rhs; }

  bool operator== (const Fraction & lhs, const Fraction & rhs) noexcept
  {
    return (lhs.numerator == rhs.numerator) && (lhs.denominator == rhs.denominator);
  }
  bool operator!= (const Fraction & lhs, const Fraction & rhs) noexcept
  {
    return !(lhs == rhs);
  }

  bool operator< (const Fraction & lhs, const Fraction & rhs) noexcept
  {
    return (lhs.numerator * rhs.denominator) < (rhs.numerator * lhs.denominator);
  }
  bool operator> (const Fraction & lhs, const Fraction & rhs) noexcept
  {
    return !((lhs < rhs) || (lhs == rhs));
  }

  bool operator<= (const Fraction & lhs, const Fraction & rhs) noexcept
  {
    return !(lhs > rhs);
  }
  bool operator>= (const Fraction & lhs, const Fraction & rhs) noexcept
  {
    return !(lhs < rhs);
  }

  Fraction & Fraction::operator++() noexcept
  {
    (*this) += 1;

    return (*this);
  }
  Fraction & Fraction::operator--() noexcept
  {
    (*this) -= 1;

    return (*this);
  }

  Fraction Fraction::operator++(int) noexcept
  {
    Fraction temp(*this);
    ++(*this);

    return temp;
  }
  Fraction Fraction::operator--(int) noexcept
  {
    Fraction temp(*this);
    --(*this);

    return temp;
  }
}
