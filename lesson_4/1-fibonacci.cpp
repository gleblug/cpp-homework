#include <iostream>

// Recursion algorithm
int fibonacci_rec(int n) {
  switch (n) {
    case 1:
      // First Fibonacci number
      return 0;
    case 2:
      // Second Fibonacci number
      return 1;
    default:
      // Find other Fibonacci numbers with recursion
      return fibonacci_rec(n - 1) + fibonacci_rec(n - 2);
  };
}

int main(int argc, char const *argv[]) {
  // Declaring variables
  int n;

  // User input
  std::cout << "Enter a number to find Fibonacci Sequence: ";
  std::cin >> n;
  std::cout << std::endl;

  // User output
  std::cout << "Your Fibonacci number is " << fibonacci_rec(n) << std::endl;

  // Exit program successfully
  return 0;
}
