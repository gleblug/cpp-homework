#include <iostream>
#include <vector>
#include <string>

void inserctionSort(std::vector<int> &array) {
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

  userInput(array);
  inserctionSort(array);
  outputArray(array);

  return 0;
}
