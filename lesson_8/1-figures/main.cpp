#include "Figure2d.hpp"
#include <vector>

int main(int argc, char const *argv[]) {

  std::vector<Figure2d*> figures{
    new Rectangle ({{0,0}, {0,3}, {1,3}, {1,0}}),
    // new Square ({{0,0}, {0,3}, {1,3}, {1,0}}), // Invalid figure
    new Square ({{0,2}, {2,4}, {4,2}, {2,0}}),
    new Circle ({2, 3}, 9),
    // new Triangle ({{1,1}, {2,2}, {3,3}}) // Invalid figure
    new Triangle ({{1,1}, {2,2}, {5,-3}})
  };

  for (auto figure: figures) {
    figure->print_info();
    std::cout << "P = " << figure->get_perimeter() << '\n'
      << "S = " << figure->get_area() << '\n' << std::endl;
  }
}
