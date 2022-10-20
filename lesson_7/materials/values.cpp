#include <iostream>

void foo(int&) {
  std::cout << "lvalue" << '\n';
}

void foo(int&&) {
  std::cout << "rvalue" << '\n';
}

int boo1() {
  int x = 1;
  return x;       // prvalue
}

int& boo2() {
  int x = 1;
  return x;       // lvalue
}

int&& boo3() {
  int x = 1;
  return std::move(x); // xvalue
}

int main(int argc, char const *argv[]) {
  int a = 1;
  int& b = a;
  int&& c = 1;

  foo(1);             // OUT: rvalue
  foo(a);             // OUT: lvalue
  foo(b);             // OUT: lvalue
  foo(c);             // OUT: lvalue
  foo(std::move(a));  // OUT: rvalue
  foo(a + 1);         // OUT: rvalue

  std::cout << "------" << '\n';

  foo(boo1());        // OUT: rvalue
  foo(boo2());        // OUT: lvalue
  foo(boo3());        // OUT: rvalue

  std::cout << "------" << '\n';

  std::cout << boo2() << '\n';

  return 0;
}
