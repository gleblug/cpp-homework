#include <vector>
#include "FigurePlot.hpp"
#include "Vec2d.hpp"

int main(int argc, char const *argv[]) {

  FigurePlot figure_plot;

  std::vector<Vec2d> triangle = {Vec2d(1, 1), Vec2d(-1, -1), Vec2d(0.5, -0.5)};

  figure_plot.plot2d(triangle);

  return 0;
}
