#pragma once
#include <vector>
#include <functional>
#include "Vec2d.hpp"
#include "Vec3d.hpp"
#include "ConsoleScreen.hpp"

class FigurePlot {
public:

  FigurePlot() = default;

  void plot2d(std::vector<Vec2d> polygon);

  void plot2d(std::function<bool(double, double)> shape);

  void animate2d();

  ~FigurePlot() = default;

};
