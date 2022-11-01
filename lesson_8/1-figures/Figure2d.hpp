#pragma once
#include<vector>
#include<string>
#include<iostream>
#include <cmath>

using vec2d = std::pair<double, double>;

inline double constexpr pi = 3.1415926535;

double distance(vec2d pt1, vec2d pt2);

// Base figure class
class Figure2d {
public:
  virtual ~Figure2d() = default;

  virtual double get_perimeter() const = 0;

  virtual double get_area() const = 0;

  virtual std::string get_info() const = 0;

  friend std::ostream &operator<<(std::ostream &stream, Figure2d const *figure);
};

std::ostream &operator<<(std::ostream &stream, Figure2d const *figure);

// Figure -> Polygon class
class Polygon : public Figure2d
{
public:
  explicit Polygon(const std::vector<vec2d> points_);

  virtual ~Polygon () = default;

  double get_perimeter() const override;

  double get_area() const override;

  virtual std::string get_info() const override {
    return "Polygon.";
  }

// protected:
  std::vector<vec2d> points;
  std::vector<double> sides;

// private:
  virtual void calculate_sides() {
    size_t size = std::size(points);
    for (size_t i = 0; i < size; i++) {
      sides.push_back(distance(points[i], points[(i + 1) % size]));
    }
  };
};

// Figure -> Polygon -> Triangle class
class Triangle: public Polygon {
public:
  explicit Triangle (const std::vector<vec2d> points);

  virtual ~Triangle () = default;

  double get_area() const override {
    double p = get_perimeter() / 2.0;

    return std::sqrt(p * (p-sides[0]) * (p-sides[1]) * (p-sides[2]));
  };

  virtual std::string get_info() const override {
    return "Triangle.";
  }
};

// Figure -> Polygon -> Quadrangle class
class Quadrangle: public Polygon {
public:
  explicit Quadrangle (const std::vector<vec2d> points);

  virtual ~Quadrangle () = default;

  virtual std::string get_info() const override {
    return "Quadrangle.";
  }
};

// Figure -> Polygon -> Quadrangle -> Parallelogram class
class Parallelogram: public Quadrangle {
public:
  explicit Parallelogram (const std::vector<vec2d> points);

  virtual ~Parallelogram () = default;

  virtual std::string get_info() const override {
    return "Parallelogram.";
  }
};

// Figure -> Polygon -> Quadrangle -> Parallelogram -> Rhombus class
class Rhombus: public virtual Parallelogram {
public:
  explicit Rhombus (const std::vector<vec2d> points);

  virtual ~Rhombus () = default;

  double get_perimeter() const override {
    return 4 * sides[0];
  }

  double get_area() const override {
    double d1 = distance(points[0], points[2]);
    double d2 = distance(points[1], points[3]);

    return 0.5 * d1 * d2;
  }

  virtual std::string get_info() const override {
    return "Rhombus.";
  }
};

// Figure -> Polygon -> Quadrangle -> Parallelogram -> Rectangle class
class Rectangle: public virtual Parallelogram {
public:
  explicit Rectangle (const std::vector<vec2d> points);

  virtual ~Rectangle () = default;

  double get_area() const override {
    return sides[0] * sides[1];
  }

  virtual std::string get_info() const override {
    return "Rectangle.";
  }
};

// Figure -> Polygon -> Quadrangle -> Parallelogram -> Rectangle & Rhombus -> Square class
class Square: public Rectangle, public Rhombus {
public:
  explicit Square (const std::vector<vec2d> points);

  virtual ~Square() = default;

  double get_perimeter() const override final {
    return Rhombus::get_perimeter();
  };

  double get_area() const override final {
    return Rectangle::get_area();
  };

  virtual std::string get_info() const override {
    return "Square.";
  }
};

// Figure -> Ellipse class
class Ellipse: public Figure2d {
public:
  explicit Ellipse (vec2d center_, double a_, double b_):
    center(center_), a(a_), b(b_) {  }

  virtual ~Ellipse () = default;

  virtual double get_perimeter() const override final {
    return 4 * (pi * a * b + (a - b) * (a - b)) / (a + b);
  }

  virtual double get_area() const override final {
    return pi * a * b;
  };

  virtual std::string get_info() const override {
    return "Ellipse. Сoefficients of canonical equation: a=" +  std::to_string(a) + " b=" + std::to_string(b);
  }

protected:
  vec2d center;
  double a;
private:
  double b;
};

// Figure -> Ellipse -> Circle class
class Circle: public Ellipse {
public:
  explicit Circle (vec2d center, double radius):
    Ellipse(center, radius, radius) {  };

  virtual ~Circle () = default;

  virtual std::string get_info() const override {
    return "Circle. Radius: r=" + std::to_string(a);
  }
};
