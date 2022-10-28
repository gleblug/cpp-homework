#pragma once
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

// Base figure class
class Figure2d {
public:
  Figure2d() = default;

  virtual double get_perimeter() const;

  virtual double get_area() const;

  virtual void print_info() const;

  virtual std::pair<double, double> get_barycenter() const;

  virtual void extent(const double scale);

  virtual void rotate(const double degree);

  virtual ~Figure2d() = default;
};

// Figure -> Polygon class
class Polygon: public Figure2d {
public:
  Polygon(const std::vector<std::pair<double, double>> points):
    m_points(points) {  };

  double get_perimeter() const override;

  double get_area() const override;

  void print_info() const override;

  std::pair<double, double> get_barycenter() const override;

  void extent(const double scale) override;

  void rotate(const double degree) override;

private:
  std::vector<std::pair<double, double>> m_points;
};

// Figure -> Polygon -> Triangle class
class Triangle: public Polygon {
public:
  Triangle (const std::vector<std::pair<double, double>> points):
    Polygon(points) {
    if (points.size() != 3) error(Exceptions::invalid_number_of_points);
  }
  virtual ~Triangle ();
};

// Figure -> Polygon -> Quadrangle class
class Quadrangle: public Polygon {
private:

public:
  Quadrangle ();
  virtual ~Quadrangle ();
};

// Figure -> Polygon -> Quadrangle -> Parallelogram class
class Parallelogram: public Quadrangle {
private:

public:
  Parallelogram ();
  virtual ~Parallelogram ();
};

// Figure -> Polygon -> Quadrangle -> Parallelogram -> Rhombus class
class Rhombus: public Parallelogram {
private:

public:
  Rhombus ();
  virtual ~Rhombus ();
};

// Figure -> Polygon -> Quadrangle -> Parallelogram -> Rectangle class
class Rectangle: public Parallelogram {
private:

public:
  Rectangle ();
  virtual ~Rectangle ();
};

// Figure -> Polygon -> Quadrangle -> Parallelogram -> Rectangle & Rhombus -> Square class
class Square: public Rectangle, public Rhombus {
private:

public:
  Square ();
  virtual ~Square ();
};

// Figure -> Ellipse class
class Ellipse: public Figure2d {
private:

public:
  Ellipse ();
  virtual ~Ellipse ();
};

// Figure -> Ellipse -> Circle class
class Circle: public Ellipse {
private:

public:
  Circle ();
  virtual ~Circle ();
};
