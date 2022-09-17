/*
Main program
MAAAAIIIN!
*/

#include <iostream>
#include <iomanip>
#include <sstream>


void print_smth() {
  std::cout << "Print smth important: " << 3.1415926535 << std::endl;
}

void greeting(std::string name) {
  std::cout << "Hello, " << name << "!" << std::endl;
}

void ending(std::string name) {
  std::cout << "Goodbye, " << name << "!" << std::endl;
}

void new_func() {
  std::cout << "New func!" << std::endl;
}

int main() {
  const std::string NAME = "Umar";

  std::cout << "Hello git!" << std::endl;

  greeting(NAME);
  print_smth();
  ending(NAME);
  print_smth();
}
