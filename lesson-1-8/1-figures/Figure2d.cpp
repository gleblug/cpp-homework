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

double distance(vec2d pt1, vec2d pt2) {
  return std::sqrt((pt2.first - pt1.first) * (pt2.first - pt1.first) + (pt2.second - pt1.second) * (pt2.second - pt1.second));
};

std::ostream& operator<<(std::ostream& stream, Figure2d const * figure) {
  stream << figure->get_info();
  return stream;
}

Polygon::Polygon(const std::vector<vec2d> points_):
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
  for (size_t i = 1; i < std::size(points) - 1; i++) {
    Triangle piece({points[0], points[i], points[i + 1]});
    area += piece.get_area();
  }

  return area;
}


Triangle::Triangle (const std::vector<vec2d> points):
  Polygon(points) {
  if (std::size(points) != 3) error(Exceptions::invalid_number_of_points);

  vec2d u{points[1].first - points[0].first, points[1].second - points[0].second};
  vec2d v{points[1].first - points[2].first, points[1].second - points[2].second};

  if ((u.second == 0 && v.second == 0) ||
    ((u.second != 0 && v.second != 0) &&
    (u.first * v.second == v.first * u.second)
  ))
    error(Exceptions::invalid_figure);
}


Quadrangle::Quadrangle (const std::vector<vec2d> points):
  Polygon(points) {
  if (std::size(points) != 4) error(Exceptions::invalid_number_of_points);
}


Parallelogram::Parallelogram (const std::vector<vec2d> points):
  Quadrangle(points) {
  if ((sides[0] != sides[2]) || (sides[1] != sides[3])) error(Exceptions::invalid_figure);
}


Rhombus::Rhombus (const std::vector<vec2d> points):
  Parallelogram(points) {
  if ((sides[0] != sides[1]) || (sides[2] != sides[3])) error(Exceptions::invalid_figure);
}


Rectangle::Rectangle (const std::vector<vec2d> points):
  Parallelogram(points) {
    vec2d v(
      points[1].first - points[2].first,
      points[1].second - points[2].second
    );
  vec2d u(
    points[1].first - points[0].first,
    points[1].second - points[0].second
  );

  if (u.first * v.first + u.second * v.second != 0)
    error(Exceptions::invalid_figure);
}


Square::Square(const std::vector<vec2d> points):
  Parallelogram(points), Rectangle(points), Rhombus(points) {  }
