#include "Particle.hpp"
#include <iostream>
#include <math.h>

int main(int argc, char const *argv[]) {

  Particle electron("Electron");
  electron.set_mass(9.1e-31, System_of_units::SI);
  electron.set_lifetime(INFINITY);
  electron.set_spin(1/2);
  electron.set_electrical_charge(-1.6e-19, System_of_units::SI);
  electron.set_magnetic_moment(-9.28e-24, System_of_units::SI);

  std::cout << "Electron mass:" << '\n'
    << '\t' << "SI: " << electron.get_mass(System_of_units::SI) << '\n'
    << '\t' << "CGS: " << electron.get_mass(System_of_units::CGS) << '\n'

    << "Electrical charge of electron:" << '\n'
    << '\t' << "SI: " << electron.get_electrical_charge(System_of_units::SI) << '\n'
    << '\t' << "CGS: " << electron.get_electrical_charge(System_of_units::CGS) << '\n'

    << "Magnetic moment of electron:" << '\n'
    << '\t' << "SI: " << electron.get_magnetic_moment(System_of_units::SI) << '\n'
    << '\t' << "CGS: " << electron.get_magnetic_moment(System_of_units::CGS) << '\n'

    << "Electron spin:" << '\n'
    << '\t' << electron.get_spin() << '\n'

    << "Electron lifetime: " << '\n'
    << '\t' << electron.get_lifetime() << std::endl;

  return 0;
}
