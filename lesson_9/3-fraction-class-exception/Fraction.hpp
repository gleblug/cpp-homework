#pragma once
#include <iostream>
#include <string>

/*!
 * \namespace math
 *
 * \brief Namespace that contains math tools like fractions etc
 * 
*/
namespace math {

  /*!
   * \class Fraction
   *
   * \brief Custom fraction implementation
   *
  */
  class Fraction {
  private:

    int numerator;
    int denominator;

  public:

    Fraction ();

    Fraction (int number);

    Fraction (double number);

    Fraction (int num, int den);

    ~Fraction () = default;

    friend std::ostream & operator<< (std::ostream & stream, const Fraction & frac);
    friend std::istream & operator>> (std::istream & stream, Fraction & frac);

    int get_numerator () const noexcept {
      return numerator;
    }
    unsigned int get_denominator () const noexcept {
      return denominator;
    }

    void simplify ();

    Fraction reverse () const {
      return Fraction(denominator, numerator);
    };

    int integer_part () const noexcept {
      return numerator / denominator;
    };

    Fraction fractional_part() const noexcept {
      return Fraction(numerator - integer_part() * denominator, denominator);
    };

    explicit operator double () const noexcept {
      return static_cast<double>(numerator) / denominator;
    };

    Fraction & operator+= (const Fraction & other);
    Fraction & operator-= (const Fraction & other);
    Fraction & operator*= (const Fraction & other);
    Fraction & operator/= (const Fraction & other);

    friend Fraction operator+ (const Fraction & lhs, const Fraction & rhs);
    friend Fraction operator- (const Fraction & lhs, const Fraction & rhs);
    friend Fraction operator* (const Fraction & lhs, const Fraction & rhs);
    friend Fraction operator/ (const Fraction & lhs, const Fraction & rhs);

    friend bool operator== (const Fraction & lhs, const Fraction & rhs);
    friend bool operator!= (const Fraction & lhs, const Fraction & rhs);

    friend bool operator< (const Fraction & lhs, const Fraction & rhs);
    friend bool operator> (const Fraction & lhs, const Fraction & rhs);

    friend bool operator<=(const Fraction &lhs, const Fraction &rhs);
    friend bool operator>=(const Fraction &lhs, const Fraction &rhs);

    Fraction& operator++();
    Fraction& operator--();

    Fraction operator++(int);
    Fraction operator--(int);
  };
}
