#include <iostream>
#include <cmath>
#include <Windows.h>
#include "Vec2d.hpp"
#include "Vec3d.hpp"
#include "ConsoleScreen.hpp"
#include "FigurePlot.hpp"


void FigurePlot::plot2d(std::vector<Vec2d> polygon) {
  double size = polygon[0].x;
  for (auto point: polygon) {
    if (abs(point.x) > size) size = abs(point.x);
    if (abs(point.y) > size) size = abs(point.y);
  }

  ConsoleScreen screen(size);

  std::cout << size << '\n';

  for (size_t i = 0; i < polygon.size() - 1; i++) {
    screen.add_line(polygon[i], polygon[i + 1]);
  }
  if (polygon.size() > 2) screen.add_line(polygon[polygon.size() - 1], polygon[0]);

  screen.show();
}

void FigurePlot::plot2d(std::function<bool(double, double)> shape) {

}


void FigurePlot::animate2d() {
  // for (size_t t = 0; t < 1000000; t++) {
  //   for (size_t i = 0; i < width; i++) {
  //     for (size_t j = 0; j < height; j++) {
  //       Vec2d uv = Vec2d(i, j) / Vec2d(width, height) * 2.0 - 1.0;
  //
  //       uv.x *= aspect * pixel_aspect;
  //       uv.x += sin(t * 0.1);
  //
  //       char pixel = ' ';
  //       double dist = sqrt(uv.x * uv.x + uv.y * uv.y);
  //       int color = (int)((1 - dist) * gradient_size);
  //
  //       color = clamp(color, 0, gradient_size);
  //       pixel = gradient[color];
  //
  //       screen[i + j * width] = pixel;
  //     }
  //   }
  //
  //   show_screen();
  //   Sleep(40);
  //   ++t;
  // }
}
