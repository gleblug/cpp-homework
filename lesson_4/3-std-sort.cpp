#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <sstream>
#include <string>

void userInput(std::vector<int> &array)
{
  std::cout << "\x1B[36m" << "Input an array of INTEGERS (splitter = ' '):" << "\033[0m" << std::endl;

  // Declaring variables
  std::string input;
  std::stringstream streamInput;

  int elem;
  std::string wrongElem;

  // Get first line from input stream to string 'input'
  std::getline(std::cin, input);

  // Push 'input' to string stream
  streamInput << input;

  // Push every elem from streamInput to array as integer while it's not empty
  while (streamInput >> elem) {
    array.push_back(elem);
  }
  std::cout << std::endl;
}

void userOutput(std::vector<int> const &array, std::string message)
{
  std::cout << "\x1B[32m" << message << "\033[0m" << std::endl;

  for (int const &elem: array) {
    std::cout << elem << " ";
  }

  std::cout << '\n' << std::endl;
}

int main(int argc, char const *argv[]) {

  // Declaring variables
  std::vector<int> array;

  std::function<bool(int, int)> ruleAscending = [](int a, int b){ return a < b; };
  std::function<bool(int, int)> ruleDescending = [](int a, int b){ return a > b; };

  // User input
  userInput(array);

  // Ascending
  std::sort(std::begin(array), std::end(array), ruleAscending);
  userOutput(array, "Ascending sort:");

  // Descending
  std::sort(std::begin(array), std::end(array), ruleDescending);
  userOutput(array, "Descending sort:");

  // Exit program successfully
  return 0;
}
