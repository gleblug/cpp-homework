#pragma once
#include <string>
#include "Vec2d.hpp"
#include "Vec3d.hpp"

class ConsoleScreen {
public:

  ConsoleScreen(double size_);

  void add_line(Vec2d point1, Vec2d point2);

  void clear();

  void show() const;

  virtual ~ConsoleScreen() = default;

private:

  size_t        width;
  size_t        height;
  double        aspect;
  double        pixel_aspect;
  double        size;

  char *        screen;

};
