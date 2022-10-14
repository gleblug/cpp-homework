#include "header.hpp"

double function(double x) {
  return x * x;
} // Первое определение -- ERROR: multiple definition of `function(double)';
  // Второе -- в secondary.cpp
  
  // Для предотвращения ошибки нужно определеть объект в конкретном месте
  // одной единцицы трансляции.

int main(int argc, char const *argv[]) {

  return 0;
}
