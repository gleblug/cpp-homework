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

  std::pair<double, double> u{points[1].first - points[0].first, points[1].second - points[0].second};
  std::pair<double, double> v{points[1].first - points[2].first, points[1].second - points[2].second};

  if ((u.second == 0 && v.second == 0) ||
    ((u.second != 0 && v.second != 0) &&
    (u.first * v.second == v.first * u.second)
  ))
    error(Exceptions::invalid_figure);
}


Quadrangle::Quadrangle (const std::vector<std::pair<double, double>> points):
  Polygon(points) {
  if (points.size() != 4) error(Exceptions::invalid_number_of_points);
}


Parallelogram::Parallelogram (const std::vector<std::pair<double, double>> points):
  Quadrangle(points) {
  if ((sides[0] != sides[2]) || (sides[1] != sides[3])) error(Exceptions::invalid_figure);
}


Rhombus::Rhombus (const std::vector<std::pair<double, double>> points):
  Parallelogram(points) {
  if ((sides[0] != sides[1]) || (sides[2] != sides[3])) error(Exceptions::invalid_figure);
}


Rectangle::Rectangle (const std::vector<std::pair<double, double>> points):
  Parallelogram(points) {
    std::pair<double, double> v(
      points[1].first - points[2].first,
      points[1].second - points[2].second
    );
  std::pair<double, double> u(
    points[1].first - points[0].first,
    points[1].second - points[0].second
  );

  if (u.first * v.first + u.second * v.second != 0)
    error(Exceptions::invalid_figure);
}


Square::Square(const std::vector<std::pair<double, double>> points):
  Parallelogram(points), Rectangle(points), Rhombus(points) {  }
