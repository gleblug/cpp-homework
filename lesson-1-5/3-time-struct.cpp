#include <iostream>
#include <iomanip>

struct Time {
  unsigned int year: 12;
  unsigned int month: 4;
  unsigned int day: 5;
  unsigned int hours: 5;
  unsigned int minutes: 6;
  unsigned int seconds: 6;
  unsigned int milliseconds: 10;
};

void print_time(Time time) {
  std::cout << std::setfill('0')
            << std::setw(2) << time.hours << ':'
            << std::setw(2) << time.minutes << ':'
            << std::setw(2) << time.seconds << '.'
            << std::setw(3) << time.milliseconds << '\n'
            << std::setw(2) << time.day << '.'
            << std::setw(2) << time.month << '.'
            << std::setw(4) << time.year << "\n\n";
}

int main(int argc, char const *argv[]) {
  // Time max_time{4095, 12, 31, 23, 59, 59, 999};
  Time world_war_first{1914,7,28,19,0,0,0};
  Time new_year{2022, 12, 31, 23, 59, 59, 0};

  print_time(world_war_first);
  // print_time(max_time);
  print_time(new_year);

  std::cout << sizeof(Time) << '\n';

  return 0;
}
