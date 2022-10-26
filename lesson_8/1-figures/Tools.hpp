#pragma once
#include <cmath>
#include <string>
#include <iostream>

double clamp(double value, double min, double max) {
  return std::max(std::min(value, max), min);
}

double fpart(double number) {
  return number - static_cast<long>(number);
}

long ipart(double number) {
  return static_cast<long>(number);
}

void warning(std::string warn_message) {
  std::cerr << "**WARNING** " << warn_message << '\n';
}

void error(std::string error_message) {
  std::cerr << "**ERROR**   " << error_message << '\n';
}

struct Limits {
  Limits (double number):
    min(number),
    max(number) {  }

  double min;
  double max;
};
