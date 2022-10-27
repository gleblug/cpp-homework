#pragma once

// Base figure class
class Figure2d {
private:

public:
  Figure2d ();
  virtual ~Figure2d ();
};

// Figure -> Polygon class
class Polygon: public Figure2d {
private:

public:
  Polygon ();
  virtual ~Polygon ();
};

// Figure -> Polygon -> Triangle class
class Triangle: public Polygon {
private:

public:
  Triangle ();
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
