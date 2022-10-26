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
   * \bried Custom fraction implementation
   *
  */
  class Fraction {
  private:

    int  numerator;
    unsigned int  denominator;

  public:

    Fraction ();

    Fraction (int number);

    Fraction (double number);

    Fraction (int num, int den);

    ~Fraction () = default;

    friend std::ostream & operator<< (std::ostream & stream, const Fraction & frac);
    friend std::istream & operator>> (std::istream & stream, Fraction & frac);

    // int get_numerator () const {
    //   return numerator;
    // }
    // unsigned int get_denominator () const {
    //   return denominator;
    // }

    void simplify ();

    Fraction reverse () const;

    int integer_part () const {
      return numerator / denominator;
    };

    Fraction fractional_part() const {
      return Fraction(numerator - integer_part() * denominator, denominator);
    };

    explicit operator double () const {
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

    friend bool operator<= (const Fraction & lhs, const Fraction & rhs);
    friend bool operator>= (const Fraction & lhs, const Fraction & rhs);

    Fraction& operator++();
    Fraction& operator--();

    Fraction operator++(int);
    Fraction operator--(int);
  };
}

enum class Exceptions {
  division_by_zero
};

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
  exit(static_cast<int>(exception));
}
