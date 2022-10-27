#pragma once

class Figure3d {
private:

public:
  Figure3d ();
  virtual ~Figure3d ();
};

class Shape: public Figure3d {
private:

public:
  Shape ();
  virtual ~Shape ();
};

class Tetrahedron {
private:

public:
  Tetrahedron ();
  virtual ~Tetrahedron ();
};

class Parallelepiped: public Shape {
private:

public:
  Parallelepiped ();
  virtual ~Parallelepiped ();
};

class RectangularParallelepiped: public Parallelepiped {
private:

public:
  RectangularParallelepiped ();
  virtual ~RectangularParallelepiped ();
};

class Rhombohedron: public Parallelepiped {
private:

public:
  Rhombohedron ();
  virtual ~Rhombohedron ();
};

class Cube: public RectangularParallelepiped, Rhombohedron {
private:

public:
  Cube ();
  virtual ~Cube ();
};

class Ellipsoid: public Figure3d {
private:

public:
  Ellipsoid ();
  virtual ~Ellipsoid ();
};

class Sphere: public Ellipsoid {
private:

public:
  Sphere ();
  virtual ~Sphere ();
};
