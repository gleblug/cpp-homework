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
    stream << frac.get_numerator() << '/' << frac.denominator;

    return stream;
  }

  std::istream & operator>> (std::istream & stream, Fraction & frac)
  {
    long int numerator;

    std::string str_num;
    std::string str_den;
    std::string line;
    size_t div_ind;

    stream >> line;
    div_ind = line.find("/");

    str_num = line.substr(0, div_ind);
    str_den = line.substr(div_ind + 1, line.size() - div_ind - 1);

    numerator = std::stoi(str_num);

    frac.minus = numerator < 0;
    frac.numerator = std::abs(numerator);
    frac.denominator = std::stoi(str_den);

    frac.simplify();

    return stream;
  }

  void Fraction::simplify()
  {
    int gcd = std::gcd(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
  }

  Fraction Fraction::reverse () const
  {
    if (numerator) {
      return Fraction(get_denominator(), get_numerator());
    }

    std::cerr << "~~~ Division by zero! ~~~";
    return Fraction(1);
  }

  Fraction & Fraction::operator+=(const Fraction & other)
  {
    long int numerator_;
    numerator_ = get_numerator() * other.denominator + other.get_numerator() * denominator;

    minus = (numerator_ < 0);
    numerator = std::abs(numerator_);
    denominator = denominator * other.denominator;

    simplify();

    return (*this);
  }

  Fraction & Fraction::operator-= (const Fraction & other)
  {
    long int numerator_;
    numerator_ = get_numerator() * other.denominator - other.get_numerator() * denominator;

    minus = (numerator_ < 0);
    numerator = std::abs(numerator_);
    denominator = denominator * other.denominator;

    simplify();

    return (*this);
  }

  Fraction & Fraction::operator*= (const Fraction & other)
  {
    minus = ((int)minus + (int)other.minus) % 2;
    numerator *= other.numerator;
    denominator *= other.denominator;

    simplify();

    return (*this);
  }

  Fraction & Fraction::operator/= (const Fraction & other)
  {
    minus = ((int)minus + (int)other.minus) % 2;
    numerator *= other.denominator;
    denominator *= other.numerator;
    
    simplify();

    return (*this);
  }

  Fraction operator+ (const Fraction & lhs, const Fraction & rhs) { return Fraction(lhs) += rhs; }
  Fraction operator- (const Fraction & lhs, const Fraction & rhs) { return Fraction(lhs) -= rhs; }
  Fraction operator* (const Fraction & lhs, const Fraction & rhs) { return Fraction(lhs) *= rhs; }
  Fraction operator/ (const Fraction & lhs, const Fraction & rhs) { return Fraction(lhs) /= rhs; }

  bool operator== (const Fraction & lhs, const Fraction & rhs)
  {
    return (lhs.minus == rhs.minus) && \
    (lhs.numerator == rhs.numerator) && \
    (lhs.denominator == rhs.denominator);
  }
  bool operator!= (const Fraction & lhs, const Fraction & rhs)
  {
    return !(lhs == rhs);
  }

  bool operator< (const Fraction & lhs, const Fraction & rhs)
  {
    return (lhs.get_numerator() * rhs.get_denominator()) < (rhs.get_numerator() * lhs.get_denominator());
  }
  bool operator> (const Fraction & lhs, const Fraction & rhs)
  {
    return (lhs.get_numerator() * rhs.get_denominator()) > (rhs.get_numerator() * lhs.get_denominator());
  }

  bool operator<= (const Fraction & lhs, const Fraction & rhs)
  {
    return (lhs < rhs) || (lhs == rhs);
  }
  bool operator>= (const Fraction & lhs, const Fraction & rhs)
  {
    return (lhs > rhs) || (lhs == rhs);;
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

}
