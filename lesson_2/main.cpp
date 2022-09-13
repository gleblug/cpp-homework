/*
Main program
MAAAAIIIN!
*/

#include <iostream>
#include <iomanip>
#include <sstream>


void print_smth() {
  std::cout << "Print smth" << std::endl;
}

void greeting(std::string name) {
  std::cout << "Hello, " << name << "!" << std::endl;
}

void ending(std::string name) {
  std::cout << "Goodbye, " << name << "!" << std::endl;
}

int main() {
  std::cout << "Hello git!" << std::endl;
  greeting("Umar");
  print_smth();
}
