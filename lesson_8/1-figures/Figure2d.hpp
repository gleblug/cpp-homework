#pragma once
#include<vector>
#include<string>
#include<iostream>
#include <cmath>

inline double const pi = 3.1415926535;

double distance(std::pair<double, double> pt1, std::pair<double, double> pt2);

// Base figure class
class Figure2d {
public:
  virtual ~Figure2d() = default;

  virtual double get_perimeter() const = 0;

  virtual double get_area() const = 0;

  virtual void print_info() const = 0;

};

// Figure -> Polygon class
class Polygon: public Figure2d {
public:
  Polygon() = delete;

  Polygon(const std::vector<std::pair<double, double>> points_);

  virtual ~Polygon () = default;

  double get_perimeter() const override;

  double get_area() const override;

  void print_info() const override {
    std::cout << "Polygon." << std::endl;
  }

protected:
  std::vector<std::pair<double, double>>  points;
  std::vector<double>                     sides;

private:
  virtual void calculate_sides() {
    for (size_t i = 0; i < points.size() - 1; i++) {
      sides.push_back(distance(points[i], points[i + 1]));
    }
    sides.push_back(distance(points[0], points[points.size() - 1]));
  };
};

// Figure -> Polygon -> Triangle class
class Triangle: public Polygon {
public:
  Triangle() = delete;

  Triangle (const std::vector<std::pair<double, double>> points);

  virtual ~Triangle () = default;

  double get_area() const override {
    double p = get_perimeter() / 2.0;

    return std::sqrt(p * (p-sides[0]) * (p-sides[1]) * (p-sides[2]));
  };

  void print_info() const override {
    std::cout << "Triangle." << std::endl;
  }
};

// Figure -> Polygon -> Quadrangle class
class Quadrangle: public Polygon {
public:
  Quadrangle () = delete;

  Quadrangle (const std::vector<std::pair<double, double>> points);

  virtual ~Quadrangle () = default;

  virtual void print_info() const override {
    std::cout << "Quadrangle." << std::endl;
  }
};

// Figure -> Polygon -> Quadrangle -> Parallelogram class
class Parallelogram: public Quadrangle {
public:
  Parallelogram () = delete;

  Parallelogram (const std::vector<std::pair<double, double>> points);

  virtual ~Parallelogram () = default;

  virtual void print_info() const override {
    std::cout << "Parallelogram." << std::endl;
  }
};

// Figure -> Polygon -> Quadrangle -> Parallelogram -> Rhombus class
class Rhombus: public virtual Parallelogram {
public:
  Rhombus () = delete;

  Rhombus (const std::vector<std::pair<double, double>> points);

  virtual ~Rhombus () = default;

  double get_perimeter() const override {
    return 4 * sides[0];
  }

  double get_area() const override {
    double d1 = distance(points[0], points[2]);
    double d2 = distance(points[1], points[3]);

    return 0.5 * d1 * d2;
  }

  virtual void print_info() const override {
    std::cout << "Rhombus." << std::endl;
  }
};

// Figure -> Polygon -> Quadrangle -> Parallelogram -> Rectangle class
class Rectangle: public virtual Parallelogram {
public:
  Rectangle () = delete;

  Rectangle (const std::vector<std::pair<double, double>> points);

  virtual ~Rectangle () = default;

  double get_area() const override {
    return sides[0] * sides[1];
  }

  virtual void print_info() const override {
    std::cout << "Rectangle." << std::endl;
  }
};

// Figure -> Polygon -> Quadrangle -> Parallelogram -> Rectangle & Rhombus -> Square class
class Square: public Rectangle, public Rhombus {
public:
  Square (const std::vector<std::pair<double, double>> points);

  virtual ~Square() = default;

  double get_perimeter() const override final {
    return Rhombus::get_perimeter();
  };

  double get_area() const override final {
    return Rectangle::get_perimeter();
  };

  virtual void print_info() const override {
    std::cout << "Square." << std::endl;
  }
};

// Figure -> Ellipse class
class Ellipse: public Figure2d {
public:
  Ellipse () = delete;

  Ellipse (std::pair<double, double> center_, double a_, double b_):
    center(center_), a(a_), b(b_) {  }

  virtual ~Ellipse () = default;

  virtual double get_perimeter() const override final {
    return 4 * (pi * a * b + (a - b) * (a - b)) / (a + b);
  }

  virtual double get_area() const override final {
    return pi * a * b;
  };

  virtual void print_info() const override {
    std::cout << "Ellipse. Сoefficients of canonical equation: a=" << a << " b=" << b << std::endl;
  }

protected:
  std::pair<double, double> center;
  double a;
private:
  double b;
};

// Figure -> Ellipse -> Circle class
class Circle: public Ellipse {
public:
  Circle() = delete;

  Circle (std::pair<double, double> center, double radius):
    Ellipse(center, radius, radius) {  };

  virtual ~Circle () = default;

  virtual void print_info() const override {
    std::cout << "Circle. Radius: r=" << a << std::endl;
  }
};
