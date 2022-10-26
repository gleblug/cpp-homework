#pragma once

class Vec2d {
public:
  double x;
  double y;


  Vec2d(double value):
    x(value), y(value) {}
  Vec2d(double _x, double _y):
    x(_x), y(_y) {}


  Vec2d operator+(Vec2d const& other) {
    return Vec2d(x + other.x, y + other.y);
  }
  Vec2d operator-(Vec2d const& other) {
    return Vec2d(x - other.x, y - other.y);
  }
  Vec2d operator*(Vec2d const& other) {
    return Vec2d(x * other.x, y * other.y);
  }
  Vec2d operator/(Vec2d const& other) {
    return Vec2d(x / other.x, y / other.y);
  }
};
