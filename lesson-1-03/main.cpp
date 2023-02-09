#include <iostream>

void f (int& a) {
  a++;
  std::cout << "a(func)=" << a << '\n'; // out: 3
}

int main() {
  int a = 2;
  int& link = a; // создание ссылки (теперь link тождественно равен a) -- альтернативное имя объекта

  f(a); // изменяет объект по ссылке a или link

  std::cout << "a=" << a << '\n'; // out: 3
}

/*
ВОПРОСЫ

ctrl+D -???
linter std::size
про точку с запятой (почему где и как ставится)
когда ооп?

*/
