#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

inline double constexpr pi = 3.1415926535;

class vec3d {
public:
    vec3d(double x_, double y_, double z_): x(x_), y(y_), z(z_) {  }

    vec3d(double a) : x(a), y(a), z(a) {  }

    vec3d &operator+=(const vec3d &other);
    vec3d &operator-=(const vec3d &other);
    
    vec3d &operator^=(const vec3d &other);

    friend vec3d operator+(const vec3d &lhs, const vec3d &rhs);
    friend vec3d operator-(const vec3d &lhs, const vec3d &rhs);
    // scalar multiply
    friend double operator%(const vec3d &lhs, const vec3d &rhs);
    // vector mutiply
    friend vec3d operator^(const vec3d &lhs, const vec3d &rhs);
    
    double module() {
        return std::sqrt(x * x + y * y + z * z);
    }

    double x;
    double y;
    double z;
};


class Figure3d {
public:
    virtual ~Figure3d() = default;

    virtual double get_surface_area() const = 0;

    virtual double get_volume() const = 0;

    virtual std::string get_info() const = 0;

    friend std::ostream &operator<<(std::ostream &stream, Figure3d const *figure);
};

std::ostream &operator<<(std::ostream &stream, Figure3d const *figure);

class Polyhedron : public Figure3d {
public:
    explicit Polyhedron(const std::vector<vec3d> points_): points(points_) {  }

    virtual ~Polyhedron () = default;

    virtual std::string get_info() const override {
        return "Polyhedron";
    }

protected:
    std::vector<vec3d> points;
};

class Pyramid : public Polyhedron {
public:
    explicit Pyramid(const std::vector<vec3d> points_): Polyhedron(points_) {  }

    virtual ~Pyramid () = default;

    virtual double get_surface_area() const override;

    virtual double get_volume() const override;

    virtual std::string get_info() const override {
        return "Pyramid";
    }
};

class RectangularParallelepiped : public Polyhedron {
public:
    explicit RectangularParallelepiped(const std::vector<vec3d> points_): Polyhedron(points_) {  }

    virtual ~RectangularParallelepiped () = default;

    virtual double get_surface_area() const override final;

    virtual double get_volume() const override final;

    virtual std::string get_info() const override {
        return "Rectangular parallelepiped";
    }
};

class Cube : public RectangularParallelepiped {
public:
    explicit Cube(const std::vector<vec3d> points_): RectangularParallelepiped(points_) {  }

    virtual ~Cube() = default;

    virtual std::string get_info() const override
    {
        return "Cube";
    }
};


class Ellipsoid : public Figure3d {
public:
    explicit Ellipsoid (vec3d center_, double a_, double b_, double c_) : center(center_), a(a_), b(b_), c(c_) {  }

    virtual ~Ellipsoid () = default;

    virtual double get_surface_area() const override final {
        double p = 1.6;
        return 4.0 * pi * std::pow((std::pow(a * b, p) + std::pow(a * c, p) + std::pow(c * b, p)) / 3.0, 1.0 / p);
    }

    virtual double get_volume() const override final {
        return 4.0 / 3.0 * pi * a * b * c;
    }

    virtual std::string get_info() const override {
        return "Ellipsoid. Сoefficients of canonical equation: a=" + std::to_string(a) + " b=" + std::to_string(b) + " c=" + std::to_string(c);
    }

protected:
    vec3d center;
    double a;
private:
    double b;
    double c;
};

class Sphere : public Ellipsoid {
public:
    explicit Sphere(vec3d center, double radius) : Ellipsoid(center, radius, radius, radius){};

    virtual ~Sphere() = default;

    virtual std::string get_info() const override
    {
        return "Sphere. Radius: r=" + std::to_string(a);
    }
};
