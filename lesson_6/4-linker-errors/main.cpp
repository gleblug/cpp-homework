#include "header.hpp"

double function(double x) {
  return x * x;
} // Первое определение -- ERROR: multiple definition of `function(double)';
  // Второе -- в secondary.cpp
  // ........ обнаружение многократного определения

  // Для предотвращения ошибки нужно определеть объект в конкретном месте
  // одной единцицы трансляции.

int main(int argc, char const *argv[]) {
  function(1);

  second_func(2); // ERROR: undefined reference to `second_func(int)'
              // ........ ошибка линковщика с неразрешённым внешним сиволом

  return 0;
}
