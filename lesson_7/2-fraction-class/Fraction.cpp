#include "Fraction.hpp"
#include <string>
#include <cmath>
#include <iostream>
#include <numeric>

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

  std::ostream & operator<< (std::ostream & stream, const Fraction & frac)
  {
    stream << (frac.minus ? "-" : "") << frac.numerator << '/' << frac.denominator;

    return stream;
  }

  std::istream & operator>> (std::istream & stream, Fraction & frac)
  {
    std::string line;
    std::string str_num;
    std::string str_den;
    size_t div_ind;

    std::getline(stream, line);

    div_ind = line.find("/");
    frac.minus = (line[0] == '-');

    str_num = line.substr((size_t)frac.minus, div_ind - (size_t)frac.minus);
    str_den = line.substr();

    frac.numerator = std::stoi(str_num);
    frac.denominator = std::stoi(str_den);

    return stream;
  }

  void Fraction::simplify()
  {
    int gcd = std::gcd(numerator, denominator);
    numerator %= gcd;
    denominator %= gcd;
  }

  Fraction & Fraction::operator+=(const Fraction & other)
  {
    numerator += other.numerator;
    simplify();

    return (*this);
  }

  Fraction & Fraction::operator-= (const Fraction & other)
  {
    numerator -= other.numerator;
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
    numerator /= other.numerator;
    denominator /= other.denominator;
    simplify();

    return (*this);
  }

  Fraction operator+ (const Fraction & lhs, const Fraction & rhs) { return Fraction(lhs) += rhs; }
  Fraction operator- (const Fraction & lhs, const Fraction & rhs) { return Fraction(lhs) -= rhs; }
  Fraction operator* (const Fraction & lhs, const Fraction & rhs) { return Fraction(lhs) *= rhs; }
  Fraction operator/ (const Fraction & lhs, const Fraction & rhs) { return Fraction(lhs) /= rhs; }

  bool operator== (const Fraction & lhs, const Fraction & rhs)
  {

  }
  bool operator!= (const Fraction & lhs, const Fraction & rhs)
  {

  }

  bool operator< (const Fraction & lhs, const Fraction & rhs);
  bool operator> (const Fraction & lhs, const Fraction & rhs);

  bool operator<= (const Fraction & lhs, const Fraction & rhs);
  bool operator>= (const Fraction & lhs, const Fraction & rhs);

  Fraction & Fraction::operator++();
  Fraction & Fraction::operator--();

  Fraction Fraction::operator++(int);
  Fraction Fraction::operator--(int);

}
