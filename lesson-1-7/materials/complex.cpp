#include <iostream>

struct Complex {
  Complex(double re, double im):
    re(re), im(im) {}
  Complex(double re):
    re(re) {}

  double re;
  double im;



  // operator double() {
  //   return re;
  // }
};

std::ostream& operator<< (std::ostream& out, const Complex& rhs) {
  out << rhs.re << "+i" << rhs.im;
  return out;
}

Complex operator+ (Complex lhs, Complex rhs) {
  auto real = lhs.re + rhs.re;
  auto imag = lhs.im + rhs.im;

  return Complex(real, imag);
}

int main(int argc, char const *argv[]) {
  Complex a(1, 2);
  Complex b(2,3);

  std::cout << a << '\n';

  return 0;
}
