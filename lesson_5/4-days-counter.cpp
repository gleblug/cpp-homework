#include <iostream>
#include <string>

enum class Months {
  january,
  february,
  march,
  april,
  may,
  june,
  jule,
  august,
  september,
  october,
  november,
  december
};

int days_in_month(int month, int year = 2022) {
  switch (static_cast<Months>(month - 1)) {
    case Months::january:
    case Months::march:
    case Months::may:
    case Months::jule:
    case Months::august:
    case Months::october:
    case Months::december:
      return 31;
    case Months::april:
    case Months::june:
    case Months::september:
    case Months::november:
      return 30;
    case Months::february:
      if (year % 4) {
        return 28;
      } else {
        return 29;
      }
    default:
      return -1;
  };
}

int main(int argc, char const *argv[]) {

  int month;

  std::cout << "Input number of month [1;12] to find out number of days:\n" << std::endl;

  std::cin >> month;
  std::cout << '\n';

  std::cout << "Number of days is " << days_in_month(month);
}
