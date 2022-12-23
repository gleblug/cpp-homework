#include "Figure3d.hpp"

vec3d &vec3d::operator+=(const vec3d &other) {
    x += other.x;
    y += other.y;
    z += other.z;

    return (*this);
}

vec3d &vec3d::operator-=(const vec3d &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return (*this);
}

vec3d& vec3d::operator^=(const vec3d &other) {
    // 1 0 0
    // 0 1 0
    double x_ = x;
    double y_ = y;
    double z_ = z;
    x = y_ * other.z - z_ * other.y; // 0
    y = z_ * other.x - x_ * other.z; // 0
    z = x_ * other.y - y_ * other.x; // 1

    return (*this);
}

vec3d operator+(const vec3d &lhs, const vec3d &rhs) {
    return vec3d(lhs) += rhs;
}

vec3d operator-(const vec3d &lhs, const vec3d &rhs) {
    return vec3d(lhs) -= rhs;
}

double operator%(const vec3d &lhs, const vec3d &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

vec3d operator^(const vec3d &lhs, const vec3d &rhs) {
    return vec3d(lhs) ^= rhs;
}

std::ostream &operator<<(std::ostream &stream, Figure3d const *figure) {
    stream << figure->get_info();
    return stream;
}

double Pyramid::get_surface_area() const {
    vec3d a = points[1] - points[0];
    vec3d b = points[2] - points[0];
    vec3d c = points[3] - points[0];

    vec3d u = points[2] - points[1];
    vec3d v = points[3] - points[1];

    double surface_area = (a ^ b).module() + (b ^ c).module() + (a ^ c).module() + (u ^ v).module();
    surface_area /= 2.0;

    return surface_area;
}

double Pyramid::get_volume() const {
    vec3d a = points[1] - points[0];
    vec3d b = points[2] - points[0];
    vec3d c = points[3] - points[0];

    return std::abs((a ^ b) % c) / 6.0;
}

double RectangularParallelepiped::get_surface_area() const {
    double surface_area;

    vec3d a = points[1] - points[0];
    vec3d b = points[3] - points[0];
    vec3d c = points[4] - points[0];

    surface_area = (a ^ b).module() + (b ^ c).module() + (a ^ c).module();
    surface_area *= 2.0;

    return surface_area;
}

double RectangularParallelepiped::get_volume() const {
    vec3d a = points[1] - points[0]; // 1  0  0
    vec3d b = points[3] - points[0]; // 0  1  0
    vec3d c = points[4] - points[0]; // 0  0 -1

    return std::abs((a ^ b) % c);
}