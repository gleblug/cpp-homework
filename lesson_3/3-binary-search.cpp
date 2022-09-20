#include <iostream>
#include <vector>
#include <cmath>

// возьмём функции из предыдущего задания:
void insertionSort(std::vector<int> &array) {
  size_t i(1);
  while (i < array.size()) {
    size_t j(i);
    while (j > 0 && array.at(j - 1) > array.at(j)) {
      std::swap(array.at(j), array.at(j - 1));
      j--;
    }
    i++;
  }
}

void userInput(std::vector<int> &array) {
  std::cout << "Input an array of integers (0 == end)" << '\n';
  // todo: добавить нормальный ввод массива (без ограничений)

  int input;
  std::cin >> input;

  while (input != 0) {
    array.push_back(input);
    std::cin >> input;
  }

  std::cout << std::endl;
}

bool binarySearch(std::vector<int> &array, int const &number) {
  // сортировка по уже реализованному алгоритму
  insertionSort(array);

  int left(0);
  int right(array.size() - 1);

  while (left <= right) {
    int m = std::floor((left + right) / 2);
    if (array.at(m) < number) {
      left = m + 1;
    } else if (array.at(m) > number) {
      right = m - 1;
    } else {
      return true;
    }
  }

  return false;
}

int main(int argc, char const *argv[]) {
  std::vector<int> array;
  int number;
  // ввод массива
  userInput(array);
  // ввод числа для поиска
  std::cout << "Input a number to search: ";
  std::cin >> number;
  // поиск и вывод результата
  std::cout << std::boolalpha << '\n' << "Is this number available in array: "
    << binarySearch(array, number) << std::endl;

  return 0;
}
