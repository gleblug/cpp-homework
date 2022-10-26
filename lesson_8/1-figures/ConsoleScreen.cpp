#include <iostream>
#include <cmath>
#include "ConsoleScreen.hpp"

ConsoleScreen::ConsoleScreen(double size_):
  width(120),
  height(30),
  aspect(120.0 / 30.0),
  pixel_aspect(12.0 / 24.0),
  size(size_)
{
  screen = new char[width * height];
  clear();
}

void ConsoleScreen::add_line(Vec2d point1, Vec2d point2) {
  point1 = point1 / size;
  point2 = point2 / size;
  double A = point2.y - point1.y;
  double B = point1.x - point2.x;
  double C = point1.x * (point1.y - point2.y) + point1.y * (point2.x - point1.x);

  std::cout << "ADD LINE: A="<<A<<" B="<<B<<" C="<<C << '\n';

  for (size_t i = 0; i < width; i++) {
    for (size_t j = 0; j < height; j++) {
      Vec2d uv = Vec2d(i, j) / Vec2d(width, height) * 2.0 - 1.0;
      uv.y = -uv.y;
      uv.x *= aspect * pixel_aspect;


      char pixel = 'W';
      double distance = std::abs(A * uv.x + B * uv.y + C) / sqrt(A * A + B * B);
      // std::cout << distance << '\n';
      if (
        (distance < 0.03) &&
        (std::min(point1.x, point2.x) < uv.x && uv.x < std::max(point1.x, point2.x)) &&
        (std::min(point1.y, point2.y) < uv.y && uv.y < std::max(point1.y, point2.y))
      ) screen[i + j * width] = pixel;
    }
  }
}

void ConsoleScreen::clear() {
  for (size_t i = 0; i < width; i++) {
    for (size_t j = 0; j < height; j++) {
      screen[i + j * width] = ' ';
    }
  }
}

void ConsoleScreen::show() const {
  std::cout << std::endl << screen;
}
