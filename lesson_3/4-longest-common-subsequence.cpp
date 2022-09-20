/*
Здесь в качестве объектов для сравнения используются две строки, которые
пользователь вводит с клавиатуры. В общем случае и внеся небольшие правки в программу
алгоритм распространяется на любые типизированные последовательности объектов.
*/

#include <iostream>
#include <vector>
#include <string>

// служебная функция вывода матрицы в консоль
// void printMatrix(std::vector<std::vector<int>> const &matrix) {
//   for (std::vector<int> const &row: matrix) {
//     for (int const &elem: row) {
//       std::cout << elem << ' ';
//     }
//     std::cout << '\n';
//   }
// }

std::vector<std::vector<int>> fillDynMatrix(
  std::string const &x,
  std::string const &y
) {

  std::vector<int> row(y.size() + 1, 0);
  std::vector<std::vector<int>> matrix(x.size() + 1, row);

  for (size_t x_i = 1; x_i <= x.size(); x_i++) {
    for (size_t y_i = 1; y_i <= y.size(); y_i++) {
      if (x.at(x_i - 1) == y.at(y_i - 1)) {
        matrix.at(x_i).at(y_i) = matrix.at(x_i - 1).at(y_i - 1) + 1;
      } else {
        matrix.at(x_i).at(y_i) = std::max(matrix.at(x_i).at(y_i - 1), matrix.at(x_i - 1).at(y_i));
      }
    }
  }

  return matrix;
}


std::vector<char> LCSDyn(
  std::string const &x,
  std::string const &y
) {

  std::vector<std::vector<int>> matrix = fillDynMatrix(x, y);
  std::vector<char> maxSubsequence;

  int x_i(x.size() - 1);
  int y_i(y.size() - 1);

  while (x_i >= 0 && y_i >= 0) {
    if (x.at(x_i) == y.at(y_i)) {
      maxSubsequence.push_back(x.at(x_i));
      x_i--;
      y_i--;
    } else if (matrix.at(x_i).at(y_i + 1) > matrix.at(x_i + 1).at(y_i)) {
      x_i--;
    } else {
      y_i--;
    }
  }

  return maxSubsequence;
}


int main(int argc, char const *argv[]) {
  // declaring variables
  std::string x;
  std::string y;
  std::vector<char> maxSubsequence;

  // user input
  std::cout << "Input two strings without spaces:" << '\n';
  std::cin >> x >> y;
  std::cout << std::endl;

  // std::vector<std::vector<int>> matrix = fillDynMatrix(x, y);
  maxSubsequence = LCSDyn(x, y);

  std::cout << "Longest common subsequence (with lenght of " << maxSubsequence.size() << "):" << '\n';
  for (size_t i = 1; i <= maxSubsequence.size(); i++) {
    std::cout << maxSubsequence.at(maxSubsequence.size() - i);
  }
  std::cout << std::endl;

  return 0;
}
