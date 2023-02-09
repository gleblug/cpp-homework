#include <iostream>
#include <vector>
#include <string>

void insertionSort(std::vector<int> &array) {
  for (size_t i = 1; i < array.size(); i++) {
    for (size_t j = i; j > 0 && array.at(j - 1) > array.at(j); j--) {
      std::swap(array.at(j), array.at(j - 1));
    }
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

void outputArray(std::vector<int> const &array) {
  std::cout << "Sorted array:" << '\n';
  for (int const &num: array) {
    std::cout << num << ' ';
  }
  std::cout << std::endl;
}

int main(int argc, char const *argv[]) {
  std::vector<int> array;
  // ввод массива
  userInput(array);
  // сортировка массива
  insertionSort(array);
  // вывод массива
  outputArray(array);

  return 0;
}
