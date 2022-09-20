/*
Здесь в качестве объектов для сравнения используются две строки, которые
пользователь вводит с клавиатуры. В общем случае и внеся небольшие правки в программу
алгоритм распространяется на любые типизированные последовательности объектов.
*/

#include <iostream>
#include <vector>
#include <string>

void fillDynMatrix(
  std::vector<std::vector<int>> &matrix,
  std::string const &x,
  std::string const &y
) {

}

void LCSDyn() {

}

int main(int argc, char const *argv[]) {
  // declaring variables
  std::vector<std::vector<unsigned int>> matrix;
  std::string x;
  std::string y;

  // user input
  std::cout << "Input two strings without spaces" << '\n';
  std::cin >> x >> y;

  std::cout << x << '\n' << y << std::endl;


  return 0;
}
