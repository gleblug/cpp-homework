#include "Figure2d.hpp"
#include<vector>
#include<string>
#include<iostream>
#include <cmath>

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

double distance(std::pair<double, double> pt1, std::pair<double, double> pt2) {
  return std::sqrt((pt2.first - pt1.first) * (pt2.first - pt1.first) + (pt2.second - pt1.second) * (pt2.second - pt1.second));
}

Polygon::Polygon(const std::vector<std::pair<double, double>> points_):
  points(points_) {
  if (points.size() < 5) error(Exceptions::invalid_number_of_points);
};


double Polygon::get_perimeter() const override {
  double perimeter = 0;
  for (size_t i = 0; i < points.size() - 1; i++) {
    perimeter += distance(points[i], points[i + 1]);
  }
  perimeter += distance(points[0], points[points.size() - 1]);

  return perimeter;
}

double Polygon::get_area() const override {
  double area = 0;
  for (size_t i = 1; i < points.size() - 1; i++) {
    Triangle piece(points[0], points[i], points[i + 1]);
    area += piece.get_area();
  }

  return area;
}


Triangle::Triangle (const std::vector<std::pair<double, double>> points):
  Polygon(points) {
  if (points.size() != 3) error(Exceptions::invalid_number_of_points);
}

double Triangle::get_area() const override {
  double p = get_perimeter() / 2;

  double a = distance(points[0], points[1]);
  double b = distance(points[1], points[2]);
  double c = distance(points[2], points[0]);

  return std::sqrt(p * (p-a) * (p-b) * (p-c));
}
