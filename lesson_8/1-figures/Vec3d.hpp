#pragma once

class Vec3d {
public:
  double x;
  double y;
  double z;


  Vec3d(double value):
    x(value), y(value), z(value) {}
  Vec3d(double _x, double _y, double _z):
    x(_x), y(_y), z(_z) {}


  Vec3d operator+(Vec3d const& other) {
    return Vec3d(x + other.x, y + other.y, z + other.z);
  }
  Vec3d operator-(Vec3d const& other) {
    return Vec3d(x - other.x, y - other.y, z - other.z);
  }
  Vec3d operator*(Vec3d const& other) {
    return Vec3d(x * other.x, y * other.y, z * other.z);
  }
  Vec3d operator/(Vec3d const& other) {
    return Vec3d(x / other.x, y / other.y, z / other.z);
  }
};
