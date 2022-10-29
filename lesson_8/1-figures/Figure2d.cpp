#include "Figure2d.hpp"
#include<vector>
#include<string>
#include<iostream>

enum class Exceptions {
  invalid_number_of_points
};

void error(Exceptions exception) {
  std::string error_message = "Unknown error.";
  switch (exception) {
    case Exceptions::invalid_number_of_points:
      error_message = "Invalid number of points!";
      break;
  }
  std::cerr << "ERROR: " << error_message << std::endl;
  exit(EXIT_FAILURE);
}


Triangle::Triangle (const std::vector<std::pair<double, double>> points):
  Polygon(points) {
  if (points.size() != 3) error(Exceptions::invalid_number_of_points);
}
