#include "Figure2d.hpp"
#include<vector>
#include<string>
#include<iostream>
#include <cmath>

enum class Exceptions {
  invalid_number_of_points,
  invalid_figure
};

void error(Exceptions exception) {
  std::string error_message = "Unknown error.";
  switch (exception) {
    case Exceptions::invalid_number_of_points:
      error_message = "Invalid number of points!";
      break;
    case Exceptions::invalid_figure:
      error_message = "Invalid figure!";
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

  calculate_sides();
};


double Polygon::get_perimeter() const {
  double perimeter = 0;
  for (double side: sides)
    perimeter += side;

  return perimeter;
}

double Polygon::get_area() const {
  double area = 0;
  for (size_t i = 1; i < points.size() - 1; i++) {
    Triangle piece({points[0], points[i], points[i + 1]});
    area += piece.get_area();
  }

  return area;
}


Triangle::Triangle (const std::vector<std::pair<double, double>> points):
  Polygon(points) {
  if (points.size() != 3) error(Exceptions::invalid_number_of_points);

  std::pair<double, double> A = points[0];
  std::pair<double, double> B = points[1];
  std::pair<double, double> C = points[2];

  if ((C.first - B.first) / (C.second - B.second) == (C.first - A.first) / (C.second - A.second))
    error(Exceptions::invalid_figure);
}

double Triangle::get_area() const {
  double p = get_perimeter() / 2;

  double a = sides[0];
  double b = sides[1];
  double c = sides[2];

  return std::sqrt(p * (p-a) * (p-b) * (p-c));
}


Quadrangle::Quadrangle (const std::vector<std::pair<double, double>> points):
  Polygon(points) {
  if (points.size() != 4) error(Exceptions::invalid_number_of_points);
}


Parallelogram::Parallelogram (const std::vector<std::pair<double, double>> points):
  Quadrangle(points) {
  double a = distance(points[0], points[1]);
  double b = distance(points[1], points[2]);
  double c = distance(points[2], points[3]);
  double d = distance(points[3], points[0]);

  if ((a != c) || (b != d)) error(Exceptions::invalid_figure);
}


Rhombus::Rhombus (const std::vector<std::pair<double, double>> points):
  Parallelogram(points) {
  double a = distance(points[0], points[1]);
  double b = distance(points[1], points[2]);
  double c = distance(points[2], points[3]);
  double d = distance(points[3], points[0]);

  if ((a != b) || (c != d)) error(Exceptions::invalid_figure);
}
