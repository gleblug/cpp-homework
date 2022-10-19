#include "Particle.hpp"
#include <map>
#include <iostream>


Particle::Particle(std::string const& name):
  name(name)
{  }

void Particle::set_mass(double value, System_of_units system_of_units) {
  m_mass = input_converter("mass", value, system_of_units);
}
double Particle::get_mass(System_of_units system_of_units) {
  return output_converter("mass", m_mass, system_of_units);
}


void Particle::set_electrical_charge(double value, System_of_units system_of_units) {
  m_electrical_charge = input_converter("electrical_charge", value, system_of_units);
}
double Particle::get_electrical_charge(System_of_units system_of_units) {
  return output_converter("electrical_charge", m_electrical_charge, system_of_units);
}


void Particle::set_magnetic_moment(double value, System_of_units system_of_units) {
  m_magnetic_moment = input_converter("magnetic_moment", value, system_of_units);
}
double Particle::get_magnetic_moment(System_of_units system_of_units) {
  return output_converter("magnetic_moment", m_magnetic_moment, system_of_units);
}


std::map<std::string, double> Particle::si2cgs({
  {"mass", 1e3},
  {"electrical_charge", 3e9},
  {"magnetic_moment", 1e3}
});


double Particle::input_converter(std::string type, double value, System_of_units system_of_units) {
  switch (system_of_units) {
    case System_of_units::SI:
      return value * Particle::si2cgs[type];
      break;
    case System_of_units::CGS:
      return value;
      break;
    default:
      return -1;
  }
}

double Particle::output_converter(std::string type, double value_cgs, System_of_units system_of_units) {
  switch (system_of_units) {
    case System_of_units::SI:
      return value_cgs / Particle::si2cgs[type];
      break;
    case System_of_units::CGS:
      return value_cgs;
      break;
    default:
      return -1;
  }
}
