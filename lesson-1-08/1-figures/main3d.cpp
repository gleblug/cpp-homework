#include "Figure3d.hpp"
#include <vector>

int main() {
    std::vector<Figure3d *> figures{
        new Sphere(vec3d(1, 2, 3), 4),
        new Cube({
            vec3d(0, 0, 1),
            vec3d(1, 0, 1),
            vec3d(1, 1, 1),
            vec3d(0, 1, 1),
            vec3d(0, 0, 0),
            vec3d(1, 0, 0),
            vec3d(1, 1, 0),
            vec3d(0, 1, 0)
        }),
        new Ellipsoid(vec3d(0), 1, 2, 3),
        new Pyramid({
            vec3d(0, 0, 0),
            vec3d(0, 0, 1),
            vec3d(0, 1, 0),
            vec3d(1, 0, 0)
        })
    };

    for (auto figure : figures){
        std::cout << figure << '\n'
                  << "S = " << figure->get_surface_area() << '\n'
                  << "V = " << figure->get_volume() << '\n'
                  << std::endl;
    }

    for (auto figure : figures)
        delete figure;
}
